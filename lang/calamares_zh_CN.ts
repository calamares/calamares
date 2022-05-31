<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="zh_CN" version="2.1">
  <context>
    <name>AboutData</name>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="17"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt; for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="20"/>
      <source>Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="38"/>
      <source>Copyright %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</source>
      <extracomment>Copyright year-year Name &lt;email-address&gt;</extracomment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>AutoMountManagementJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/AutoMountManagementJob.cpp" line="22"/>
      <source>Manage auto-mount settings</source>
      <translation>管理自动挂载设置</translation>
    </message>
  </context>
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="62"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>这个系统的&lt;strong&gt;引导环境&lt;/strong&gt;。&lt;br&gt;&lt;br&gt;较旧的 x86 系统只支持 &lt;strong&gt;BIOS&lt;/strong&gt;。&lt;br&gt;现代的系统则通常使用 &lt;strong&gt;EFI&lt;/strong&gt;，但若引导时使用了兼容模式，也可以变为 BIOS。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="72"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>此系统从 &lt;strong&gt;EFI&lt;/strong&gt; 引导环境启动。&lt;br&gt;&lt;br&gt;若要配置EFI环境的启动项，本安装器必须在&lt;strong&gt;EFI系统分区&lt;/strong&gt;中安装一个引导程序, 例如 &lt;strong&gt;GRUB&lt;/strong&gt;或 &lt;strong&gt;systemd-boot&lt;/strong&gt; 。这个过程是自动的，但若你选择手动分区，那你将必须手动选择或者创建。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="84"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>这个系统从 &lt;strong&gt;BIOS&lt;/strong&gt; 引导环境启动。&lt;br&gt;&lt;br&gt;
要从 BIOS 环境引导，本安装程序必须安装引导器（如 &lt;strong&gt;GRUB&lt;/strong&gt;），一般而言要么安装在分区的开头，要么就是在靠进分区表开头的 &lt;strong&gt;主引导记录&lt;/strong&gt;（推荐）中。这个步骤是自动的，除非您选择手动分区——此时您必须自行配置。</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
      <source>Master Boot Record of %1</source>
      <translation>主引导记录 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="92"/>
      <source>Boot Partition</source>
      <translation>引导分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="99"/>
      <source>System Partition</source>
      <translation>系统分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="129"/>
      <source>Do not install a boot loader</source>
      <translation>不要安装引导程序</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="147"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::BlankViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="61"/>
      <source>Blank Page</source>
      <translation>空白页</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>全局存储</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>任务队列</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>模块</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="61"/>
      <source>Type:</source>
      <translation>类型：</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="68"/>
      <location filename="../src/calamares/DebugWindow.ui" line="82"/>
      <source>none</source>
      <translation>无</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>接口：</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="102"/>
      <source>Crashes Calamares, so that Dr. Konqui can look at it.</source>
      <translation>使 Calamares 崩溃，以便 Konqui 医生可以查看它。</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="115"/>
      <source>Reloads the stylesheet from the branding directory.</source>
      <translation>从Branding目录重新载入样式表</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="141"/>
      <source>Uploads the session log to the configured pastebin.</source>
      <translation>将会话日志上传至预设的pastebin网站</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="144"/>
      <source>Send Session Log</source>
      <translation>发送会话日志</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="118"/>
      <source>Reload Stylesheet</source>
      <translation>重载样式表</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="128"/>
      <source>Displays the tree of widget names in the log (for stylesheet debugging).</source>
      <translation>在日志中显示小部件名称树（用于样式表调试）。</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="131"/>
      <source>Widget Tree</source>
      <translation>树形控件</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="239"/>
      <source>Debug information</source>
      <translation>调试信息</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Set up</source>
      <translation>建立</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Install</source>
      <translation>安装</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>任务失败(%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>出现明确抛出的任务执行失败。</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="203"/>
      <source>Done</source>
      <translation>完成</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>示例任务 (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="42"/>
      <source>Run command '%1' in target system.</source>
      <translation>在目标系统上执行 '%1'。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="42"/>
      <source> Run command '%1'.</source>
      <translation>运行命令 '%1'.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="49"/>
      <source>Running command %1 %2</source>
      <translation>正在运行命令 %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="233"/>
      <source>Running %1 operation.</source>
      <translation>正在运行 %1 个操作。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="262"/>
      <source>Bad working directory path</source>
      <translation>错误的工作目录路径</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="263"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>用于 python 任务 %2 的工作目录 %1 不可读。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="269"/>
      <source>Bad main script file</source>
      <translation>错误的主脚本文件</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="270"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>用于 python 任务 %2 的主脚本文件 %1 不可读。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="343"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>任务“%1”出现 Boost.Python 错误。</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="67"/>
      <source>Loading ...</source>
      <translation>正在加载...</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="88"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation>QML 步骤 &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="268"/>
      <source>Loading failed.</source>
      <translation>加载失败。</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="94"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation>模块&lt;i&gt;%1&lt;/i&gt;的需求检查已完成。</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="118"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>等待 %n 模块。</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="119"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n 秒)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="124"/>
      <source>System-requirements checking is complete.</source>
      <translation>已经完成系统需求检查。</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
      <source>Setup Failed</source>
      <translation>安装失败</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
      <source>Installation Failed</source>
      <translation>安装失败</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="163"/>
      <source>Error</source>
      <translation>错误</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="90"/>
      <source>&amp;Yes</source>
      <translation>&amp;是</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="91"/>
      <source>&amp;No</source>
      <translation>&amp;否</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="92"/>
      <source>&amp;Close</source>
      <translation>&amp;关闭</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="184"/>
      <source>Install Log Paste URL</source>
      <translation>安装日志粘贴 URL</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="166"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>上传失败，未完成网页粘贴。</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="178"/>
      <source>Install log posted to

%1

Link copied to clipboard</source>
      <translation>发送至

%1

的链接已保存至剪贴板 </translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="189"/>
      <source>Calamares Initialization Failed</source>
      <translation>Calamares初始化失败</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="190"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>％1无法安装。 Calamares无法加载所有已配置的模块。这个问题是发行版配置Calamares不当导致的。</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="196"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;无法加载以下模块：</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="310"/>
      <source>Continue with setup?</source>
      <translation>要继续安装吗？</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="310"/>
      <source>Continue with installation?</source>
      <translation>继续安装？</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="312"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>为了安装%2, %1 安装程序即将对磁盘进行更改。&lt;br/&gt;&lt;strong&gt;这些更改无法撤销。&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="315"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1 安装程序将在您的磁盘上做出变更以安装 %2。&lt;br/&gt;&lt;strong&gt;您将无法复原这些变更。&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="318"/>
      <source>&amp;Set up now</source>
      <translation>现在安装(&amp;S)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="318"/>
      <source>&amp;Install now</source>
      <translation>现在安装 (&amp;I)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="326"/>
      <source>Go &amp;back</source>
      <translation>返回 (&amp;B)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="376"/>
      <source>&amp;Set up</source>
      <translation>安装(&amp;S)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="376"/>
      <source>&amp;Install</source>
      <translation>安装(&amp;I)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="378"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>安装完成。关闭安装程序。</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="379"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>安装已完成。请关闭安装程序。</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="381"/>
      <source>Cancel setup without changing the system.</source>
      <translation>取消安装，保持系统不变。</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="382"/>
      <source>Cancel installation without changing the system.</source>
      <translation>取消安装，并不做任何更改。</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Next</source>
      <translation>下一步(&amp;N)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>&amp;Back</source>
      <translation>后退(&amp;B)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="403"/>
      <source>&amp;Done</source>
      <translation>&amp;完成</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="422"/>
      <source>&amp;Cancel</source>
      <translation>取消(&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="495"/>
      <source>Cancel setup?</source>
      <translation>取消安装？</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="495"/>
      <source>Cancel installation?</source>
      <translation>取消安装？</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="496"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>确定要取消当前安装吗?
安装程序将会退出，所有修改都会丢失。</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="498"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>确定要取消当前的安装吗？
安装程序将退出，所有修改都会丢失。</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="302"/>
      <source>Unknown exception type</source>
      <translation>未知异常类型</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="320"/>
      <source>unparseable Python error</source>
      <translation>无法解析的 Python 错误</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="364"/>
      <source>unparseable Python traceback</source>
      <translation>无法解析的 Python 回溯</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="371"/>
      <source>Unfetchable Python error.</source>
      <translation>无法获取的 Python 错误。</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="369"/>
      <source>%1 Setup Program</source>
      <translation>%1 安装程序</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="370"/>
      <source>%1 Installer</source>
      <translation>%1 安装程序</translation>
    </message>
  </context>
  <context>
    <name>ChangeFilesystemLabelJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="32"/>
      <source>Set filesystem label on %1.</source>
      <translation>在%1设置文件系统卷标</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="39"/>
      <source>Set filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>设置文件系统标签 &lt;strong&gt;%1&lt;/strong&gt; 至分区 &lt;strong&gt;%2&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="70"/>
      <source>The installer failed to update partition table on disk '%1'.</source>
      <translation>安装程序更新磁盘“%1”分区表失败。</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="38"/>
      <source>Gathering system information...</source>
      <translation>正在收集系统信息 ...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="139"/>
      <source>Select storage de&amp;vice:</source>
      <translation>选择存储器(&amp;V)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="140"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1029"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1077"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1174"/>
      <source>Current:</source>
      <translation>当前：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="141"/>
      <source>After:</source>
      <translation>之后：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1732"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;手动分区&lt;/strong&gt;&lt;br/&gt;您可以自行创建或重新调整分区大小。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="894"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>重复使用 %1 作为 %2 的 home 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1030"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;选择要缩小的分区，然后拖动底栏改变大小&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1048"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 将会缩减未 %2MiB，然后为 %4 创建一个 %3MiB 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1106"/>
      <source>Boot loader location:</source>
      <translation>引导程序位置：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1165"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;选择要安装到的分区&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1226"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>在此系统上找不到任何 EFI 系统分区。请后退到上一步并使用手动分区配置 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1234"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>%1 处的 EFI 系统分区将被用来启动 %2。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1242"/>
      <source>EFI system partition:</source>
      <translation>EFI 系统分区：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1402"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>这个存储器上似乎还没有操作系统。您想要怎么做？&lt;br/&gt;在任何变更应用到存储器上前，您都可以重新查看并确认您的选择。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1407"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1444"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1466"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1491"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;抹除磁盘&lt;/strong&gt;&lt;br/&gt;这将会&lt;font color="red"&gt;删除&lt;/font&gt;目前选定的存储器上所有的数据。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1411"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1440"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1462"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1487"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;并存安装&lt;/strong&gt;&lt;br/&gt;安装程序将会缩小一个分区，为 %1 腾出空间。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1415"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1449"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1470"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1495"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;取代一个分区&lt;/strong&gt;&lt;br/&gt;以 %1 &lt;strong&gt;替代&lt;/strong&gt;一个分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1434"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>这个存储器上已经有 %1 了。您想要怎么做？&lt;br/&gt;在任何变更应用到存储器上前，您都可以重新查看并确认您的选择。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1457"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>这个存储器上已经有一个操作系统了。您想要怎么做？&lt;br/&gt;在任何变更应用到存储器上前，您都可以重新查看并确认您的选择。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1482"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>这个存储器上已经有多个操作系统了。您想要怎么做？&lt;br/&gt;在任何变更应用到存储器上前，您都可以重新查看并确认您的选择。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1554"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation>此存储设备已经有操作系统，但是分区表 &lt;strong&gt;%1&lt;/strong&gt; 与所需的 &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;不同。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1577"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <translation>此存储设备 &lt;strong&gt;已挂载&lt;/strong&gt;其中一个分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1582"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <translation>该存储设备是 &lt;strong&gt;非活动RAID&lt;/strong&gt; 设备的一部分。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1701"/>
      <source>No Swap</source>
      <translation>无交换分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1710"/>
      <source>Reuse Swap</source>
      <translation>重用交换分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1713"/>
      <source>Swap (no Hibernate)</source>
      <translation>交换分区(无休眠)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1716"/>
      <source>Swap (with Hibernate)</source>
      <translation>交换分区(带休眠)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1719"/>
      <source>Swap to file</source>
      <translation>交换到文件</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="272"/>
      <source>Successfully unmounted %1.</source>
      <translation>成功卸载了 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="279"/>
      <source>Successfully disabled swap %1.</source>
      <translation>成功禁用了交换空间 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="305"/>
      <source>Successfully cleared swap %1.</source>
      <translation>成功清理了交换空间 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="319"/>
      <source>Successfully closed mapper device %1.</source>
      <translation>成功关闭了映射设备 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="332"/>
      <source>Successfully disabled volume group %1.</source>
      <translation>成功禁用了卷组  %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="371"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>清理挂载了的分区以在 %1 进行分区操作</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="377"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>正在清理挂载了的分区以在 %1 进行分区操作。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="396"/>
      <source>Cleared all mounts for %1</source>
      <translation>已清除 %1 的所有挂载点</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="33"/>
      <source>Clear all temporary mounts.</source>
      <translation>清除所有临时挂载点。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="40"/>
      <source>Clearing all temporary mounts.</source>
      <translation>正在清除所有临时挂载点。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="70"/>
      <source>Cleared all temporary mounts.</source>
      <translation>所有临时挂载点都已经清除。</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="142"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="155"/>
      <source>Could not run command.</source>
      <translation>无法运行命令</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="143"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>该命令在主机环境中运行，且需要知道根路径，但没有定义root挂载点。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="156"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>命令行需要知道用户的名字，但用户名没有被设置</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="360"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>设置键盘型号为 %1。&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="367"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>设置键盘布局为 %1/%2。</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="359"/>
      <source>Set timezone to %1/%2.</source>
      <translation>将时区设置为 %1/%2 。</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="397"/>
      <source>The system language will be set to %1.</source>
      <translation>系统语言将设置为 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="404"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>数字和日期地域将设置为 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>网络安装。（禁用：错误的设置）</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="55"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>联网安装。（已禁用：收到无效组数据）</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="57"/>
      <source>Network Installation. (Disabled: Internal error)</source>
      <translation>网络安装（因内部错误而被禁用）</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="61"/>
      <source>Network Installation. (Disabled: No package list)</source>
      <translation>网络安装（因无软件包列表而被禁用）</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="77"/>
      <source>Package selection</source>
      <translation>软件包选择</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="59"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>网络安装。（已禁用：无法获取软件包列表，请检查网络连接）</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="56"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>此计算机不满足安装 %1 的某些推荐配置。
安装可以继续，但是一些特性可能被禁用。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="60"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>此电脑未满足安装 %1 的最低需求。&lt;br/&gt;安装无法继续。&lt;a href="#details"&gt;详细信息...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="67"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>此计算机不满足安装 %1 的某些推荐配置。
安装可以继续，但是一些特性可能被禁用。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="71"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>此电脑未满足一些安装 %1 的推荐需求。&lt;br/&gt;可以继续安装，但一些功能可能会被停用。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="81"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>本程序将会问您一些问题并在您的电脑上安装及设置 %2 。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="269"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;欢迎使用 %1 的 Calamares 安装程序&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="270"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;欢迎使用 %1 设置&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="274"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;欢迎使用 %1 的 Calamares 安装程序&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="275"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;欢迎使用 %1 安装程序&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="236"/>
      <source>Your username is too long.</source>
      <translation>用户名太长。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="252"/>
      <source>'%1' is not allowed as username.</source>
      <translation>'%1' 不允许作为用户名。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="242"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>用户名必须以小写字母或下划线"_"开头</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="246"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>只允许小写字母、数组、下划线"_" 和 连字符"-"</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="301"/>
      <source>Your hostname is too short.</source>
      <translation>主机名太短。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="305"/>
      <source>Your hostname is too long.</source>
      <translation>主机名太长。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="311"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation>'%1' 不允许作为主机名。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="316"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>只允许字母、数组、下划线"_" 和 连字符"-"</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="585"/>
      <source>Your passwords do not match!</source>
      <translation>密码不匹配！</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="599"/>
      <source>OK!</source>
      <translation>确定</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="145"/>
      <source>Setup Failed</source>
      <translation>安装失败</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="145"/>
      <source>Installation Failed</source>
      <translation>安装失败</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="147"/>
      <source>The setup of %1 did not complete successfully.</source>
      <translation>%1的设置未成功完成</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="148"/>
      <source>The installation of %1 did not complete successfully.</source>
      <translation>%1的安装未成功完成</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="152"/>
      <source>Setup Complete</source>
      <translation>安装完成</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="153"/>
      <source>Installation Complete</source>
      <translation>安装完成</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="154"/>
      <source>The setup of %1 is complete.</source>
      <translation>%1 安装完成。</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="155"/>
      <source>The installation of %1 is complete.</source>
      <translation>%1 的安装操作已完成。</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="111"/>
      <source>Package Selection</source>
      <translation>软件包选择</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="113"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>请在列表中选一个产品。被选中的产品将会被安装。</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="243"/>
      <source>Packages</source>
      <translation>软件包</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="249"/>
      <source>Install option: &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation>安装选项：&lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="249"/>
      <source>None</source>
      <translation>无</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="94"/>
      <source>Summary</source>
      <translation>摘要</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="98"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation>预览——当你启动安装过程，以下行为将被执行</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="103"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>这是您开始安装后所会发生的事情的概览。</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="119"/>
      <source>Contextual Processes Job</source>
      <translation>后台任务</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>创建分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>大小(&amp;Z)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>分区类型(&amp;T)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>Primar&amp;y</source>
      <translation>主分区(&amp;Y)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>扩展分区(&amp;E)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>文件系统 (&amp;L)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>LVM 逻辑卷名称</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>挂载点(&amp;M)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="191"/>
      <source>Flags:</source>
      <translation>标记：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="224"/>
      <source>Label for the filesystem</source>
      <translation>此文件系统的卷标名</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="234"/>
      <source>FS Label:</source>
      <translation>文件系统卷标</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="66"/>
      <source>En&amp;crypt</source>
      <translation>加密(&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="194"/>
      <source>Logical</source>
      <translation>逻辑分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="199"/>
      <source>Primary</source>
      <translation>主分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="218"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="91"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>挂载点已被占用。请选择另一个。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="96"/>
      <source>Mountpoint must start with a &lt;tt&gt;/&lt;/tt&gt;.</source>
      <translation>挂载点必须以&lt;tt&gt;/&lt;/tt&gt;开头。</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="187"/>
      <source>Create new %1MiB partition on %3 (%2) with entries %4.</source>
      <translation>在 %3 (%2) 上使用 %4 建立新的 %1MiB 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="195"/>
      <source>Create new %1MiB partition on %3 (%2).</source>
      <translation>在 %3 (%2) 上建立新的 %1MiB 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="202"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>在 %4 (%3) 上创建新的 %2MiB 分区，文件系统为 %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="219"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2) with entries &lt;em&gt;%4&lt;/em&gt;.</source>
      <translation>在 &lt;strong&gt;%3&lt;/strong&gt; (%2) 上使用 &lt;em&gt;%4&lt;/em&gt; 建立新的 &lt;strong&gt;%1MiB&lt;/strong&gt; 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="228"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2).</source>
      <translation>在&lt;strong&gt;%3&lt;/strong&gt;(%2)上创建新的&lt;strong&gt;%1MiB&lt;/strong&gt;分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="235"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>在&lt;strong&gt;%4&lt;/strong&gt;(%3)上创建一个&lt;strong&gt;%2MiB&lt;/strong&gt;的%1分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="260"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="263"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>正在 %2 上创建新的 %1 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="280"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>安装程序在磁盘“%1”创建分区失败。</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>创建分区表</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>创建新分区表将删除磁盘上所有已有数据。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>您想要创建哪种分区表？</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>主引导记录 (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID 分区表 (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="41"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>在 %2 上创建新的 %1 分区表。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="49"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>在 &lt;strong&gt;%2&lt;/strong&gt; (%3) 上创建新的 &lt;strong&gt;%1&lt;/strong&gt; 分区表。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="59"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>正在 %2 上创建新的 %1 分区表。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="88"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>安装程序于 %1 创建分区表失败。</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="35"/>
      <source>Create user %1</source>
      <translation>创建用户 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="42"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>创建用户 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="125"/>
      <source>Preserving home directory</source>
      <translation>保留家目录</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="49"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="142"/>
      <source>Creating user %1</source>
      <translation>创建用户 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="150"/>
      <source>Configuring user %1</source>
      <translation>配置用户 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="158"/>
      <source>Setting file permissions</source>
      <translation>设置文件权限</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <translation>创建存储组</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="32"/>
      <source>Create new volume group named %1.</source>
      <translation>新建分卷组 %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>新建名为 &lt;strong&gt;%1&lt;/strong&gt;的分卷组。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="44"/>
      <source>Creating new volume group named %1.</source>
      <translation>新建名为 %1的分卷组。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="51"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>安装器未能创建名为'%1'的分卷组</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="38"/>
      <source>Deactivate volume group named %1.</source>
      <translation>停用分卷组 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="32"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>停用分卷组&lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>安装器未能创建名为'%1'的分卷组</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="73"/>
      <source>Delete partition %1.</source>
      <translation>删除分区 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="80"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>删除分区 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="87"/>
      <source>Deleting partition %1.</source>
      <translation>正在删除分区 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="102"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>安装程序删除分区 %1 失败。</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="143"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>此设备上有一个 &lt;strong&gt;%1&lt;/strong&gt; 分区表。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="97"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>选定的存储器是一个 &lt;strong&gt;回环&lt;/strong&gt; 设备。&lt;br&gt;&lt;br&gt;此伪设备不含一个真正的分区表，它只是能让一个文件可如块设备那样访问。这种配置一般只包含一个单独的文件系统。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="108"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>本安装程序在选定的存储器上&lt;strong&gt;探测不到分区表&lt;/strong&gt;。&lt;br&gt;&lt;br&gt;此设备要不是没有分区表，就是其分区表已毁损又或者是一个未知类型的分区表。&lt;br&gt;本安装程序将会为您建立一个新的分区表，可以自动或通过手动分割页面完成。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="91"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;此分区表类型推荐用于使用 &lt;strong&gt;EFI&lt;/strong&gt; 引导环境的系统。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="80"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;此分区表类型只建议用于使用 &lt;strong&gt;BIOS&lt;/strong&gt; 引导环境的较旧系统，否则一般建议使用 GPT。&lt;br&gt;
&lt;strong&gt;警告：&lt;/strong&gt;MSDOS 分区表是一个有着重大缺点、已被弃用的标准。&lt;br&gt;MSDOS 分区表上只能创建 4 个&lt;u&gt;主要&lt;/u&gt;分区，其中一个可以是&lt;u&gt;拓展&lt;/u&gt;分区，此分区可以再分为许多&lt;u&gt;逻辑&lt;/u&gt;分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="151"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>目前选定存储器的&lt;strong&gt;分区表&lt;/strong&gt;类型。&lt;br&gt;&lt;br&gt;变更分区表类型的唯一方法就是抹除再重新从头建立分区表，这会破坏在该存储器上所有的数据。&lt;br&gt;除非您特别选择，否则本安装程序将会保留目前的分区表。&lt;br&gt;若不确定，在现代的系统上，建议使用 GPT。</translation>
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
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>将 Dracut 的 LUKS 配置写入到 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Dracut 的“/”分区未加密，因而跳过写入 LUKS 配置</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <translation>无法打开 %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="36"/>
      <source>Dummy C++ Job</source>
      <translation>虚设 C++ 任务</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>编辑已有分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Con&amp;tent:</source>
      <translation>内容：(&amp;T)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>保留 (&amp;K)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>格式化</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>警告：格式化分区将删除所有已有数据。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>挂载点(&amp;M)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source>Si&amp;ze:</source>
      <translation>尺寸 (&amp;Z)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="139"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="146"/>
      <source>Fi&amp;le System:</source>
      <translation>文件系统 (&amp;L)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="159"/>
      <source>Flags:</source>
      <translation>标记：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="179"/>
      <source>Label for the filesystem</source>
      <translation>此文件系统的卷标名</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="189"/>
      <source>FS Label:</source>
      <translation>文件系统卷标</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="259"/>
      <source>Passphrase for existing partition</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="260"/>
      <source>Partition %1 could not be decrypted with the given passphrase.&lt;br/&gt;&lt;br/&gt;Edit the partition again and give the correct passphraseor delete and create a new encrypted partition.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>加密系统</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="43"/>
      <source>Your system does not seem to support encryption well enough to encrypt the entire system. You may enable encryption, but performance may suffer.</source>
      <translation>您的系统似乎不太支持加密，无法对整个系统进行加密。您可以启用加密，但性能可能会受到影响。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="59"/>
      <source>Passphrase</source>
      <translation>密码</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="69"/>
      <source>Confirm passphrase</source>
      <translation>确认密码</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="156"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="166"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>请在两个输入框中输入同样的密码。</translation>
    </message>
  </context>
  <context>
    <name>ErrorDialog</name>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="40"/>
      <source>Details:</source>
      <translation>详情:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="56"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>需要将安装日志粘贴到网页吗？</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="172"/>
      <source>Set partition information</source>
      <translation>设置分区信息</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="201"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition with features &lt;em&gt;%3&lt;/em&gt;</source>
      <translation>在有 &lt;em&gt;%3&lt;/em&gt; 特性的&lt;strong&gt;新&lt;/strong&gt; %2 系統分区上安裝 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="209"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>在 &lt;strong&gt;新的&lt;/strong&gt;系统分区 %2 上安装 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="218"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt; and features &lt;em&gt;%3&lt;/em&gt;.</source>
      <translation>设置 &lt;strong&gt;新的&lt;/strong&gt; 含挂载点 &lt;strong&gt;%1&lt;/strong&gt;%3 的 %2 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="226"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;%3.</source>
      <translation>设置 &lt;strong&gt;新的&lt;/strong&gt; 含挂载点 &lt;strong&gt;%1&lt;/strong&gt;%3 的 %2 分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="240"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt; with features &lt;em&gt;%4&lt;/em&gt;.</source>
      <translation>在具有功能&lt;em&gt;%4&lt;/em&gt;的 %3 系统分区&lt;strong&gt;%1&lt;/strong&gt;上安装 %2。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="259"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt; and features &lt;em&gt;%4&lt;/em&gt;.</source>
      <translation>为分区 %3  &lt;strong&gt;%1&lt;/strong&gt; 设定挂载点 &lt;strong&gt;%2&lt;/strong&gt; 与特性 &lt;em&gt;%4&lt;/em&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="268"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;%4.</source>
      <translation>设置%3 分区的挂载点</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="249"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>在 %3 系统割区 &lt;strong&gt;%1&lt;/strong&gt; 上安装 %2。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="283"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>在 &lt;strong&gt;%1&lt;/strong&gt;上安装引导程序。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="292"/>
      <source>Setting up mount points.</source>
      <translation>正在设置挂载点。</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>现在重启(&amp;R)</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="75"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;安装成功！&lt;/h1&gt;&lt;br/&gt;%1 已安装在您的电脑上了。&lt;br/&gt;您现在可以重新启动到新系统。</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="79"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;当选中此项时，系统会在您关闭安装器或点击 &lt;span style=" font-style:italic;"&gt;完成&lt;/span&gt; 按钮时立即重启&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="87"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;安装成功！&lt;/h1&gt;&lt;br/&gt;%1 已安装在您的电脑上了。&lt;br/&gt;您现在可以重新启动到新系统，或是继续使用 %2 Live 环境。</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="92"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;当选中此项时，系统会在您关闭安装器或点击 &lt;span style=" font-style:italic;"&gt;完成&lt;/span&gt; 按钮时立即重启&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="105"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;安装失败&lt;/h1&gt;&lt;br/&gt;%1 未在你的电脑上安装。&lt;br/&gt;错误信息：%2。</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="113"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;安装失败&lt;/h1&gt;&lt;br/&gt;%1 未在你的电脑上安装。&lt;br/&gt;错误信息：%2。</translation>
    </message>
  </context>
  <context>
    <name>FinishedQmlViewStep</name>
    <message>
      <location filename="../src/modules/finishedq/FinishedQmlViewStep.cpp" line="35"/>
      <source>Finish</source>
      <translation>结束</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="46"/>
      <source>Finish</source>
      <translation>结束</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="39"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>格式化在 %4 的分区 %1 (文件系统：%2，大小：%3 MB)。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="50"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>以文件系统 &lt;strong&gt;%2&lt;/strong&gt; 格式化 &lt;strong&gt;%3MB&lt;/strong&gt; 的分区 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
      <source>%1 (%2)</source>
      <comment>partition label %1 (device path %2)</comment>
      <translation>%1（%2）</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="65"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>正在使用 %2 文件系统格式化分区 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="76"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>安装程序格式化磁盘“%2”上的分区 %1 失败。</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="156"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>有至少 %1 GB 可用磁盘空间</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="158"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>没有足够的磁盘空间。至少需要 %1 GB。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="166"/>
      <source>has at least %1 GiB working memory</source>
      <translation>至少 %1 GB 可用内存</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="168"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>系统没有足够的内存。至少需要 %1 GB。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="177"/>
      <source>is plugged in to a power source</source>
      <translation>已连接到电源</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="178"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>系统未连接到电源。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="185"/>
      <source>is connected to the Internet</source>
      <translation>已连接到互联网</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="186"/>
      <source>The system is not connected to the Internet.</source>
      <translation>系统未连接到互联网。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="193"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>正以管理员(root)权限运行安装器</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="197"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>安装器未以管理员权限运行</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="198"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>安装器未以管理员权限运行</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="206"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>有一个足够大的屏幕来显示整个安装器</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="210"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>屏幕太小无法显示安装程序。</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="211"/>
      <source>The screen is too small to display the installer.</source>
      <translation>屏幕不能完整显示安装器。</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="42"/>
      <source>Collecting information about your machine.</source>
      <translation>正在收集此计算机的信息。</translation>
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
      <translation>OEM批量标识</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>无法创建目录&lt;code&gt;%1&lt;/code&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>无法打开文件&lt;code&gt;%1&lt;/code&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>无法写入文件&lt;code&gt;%1&lt;/code&gt;。</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="32"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>正在用mkinitcpio创建initramfs。</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="28"/>
      <source>Creating initramfs.</source>
      <translation>正在创建initramfs。</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="46"/>
      <source>Konsole not installed</source>
      <translation>未安装 Konsole</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="47"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>请安装 KDE Konsole 后重试！</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="118"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>正在运行脚本：&amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="41"/>
      <source>Script</source>
      <translation>脚本</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <translation>键盘</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>键盘</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System locale setting</source>
      <translation>系统语区设置</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>系统语言区域设置会影响部份命令行用户界面的语言及字符集。&lt;br/&gt;目前的设置为 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="54"/>
      <source>&amp;Cancel</source>
      <translation>取消(&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="55"/>
      <source>&amp;OK</source>
      <translation>&amp;确定</translation>
    </message>
  </context>
  <context>
    <name>LOSHJob</name>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="36"/>
      <source>Configuring encrypted swap.</source>
      <translation>配置加密交换分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="88"/>
      <source>No target system available.</source>
      <translation>没有可用的目标系统。</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="96"/>
      <source>No rootMountPoint is set.</source>
      <translation>没有设定 root 挂载点。</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="101"/>
      <source>No configFilePath is set.</source>
      <translation>未设置配置文件路径。</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;许可证&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="135"/>
      <source>I accept the terms and conditions above.</source>
      <translation>我同意如上条款。</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="137"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation>请查阅最终用户许可协议 (EULAs)。</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="142"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation>此安装过程会安装受许可条款约束的专有软件。</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="145"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation>如果您不同意这些条款，安装过程将无法继续。</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="150"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation>此安装过程会安装受许可条款约束的专有软件，用于提供额外功能和提升用户体验。</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="155"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation>如果您不同意这些条款，专有软件不会被安装，相应的开源软件替代品将被安装。</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="43"/>
      <source>License</source>
      <translation>许可证</translation>
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
      <translation>&lt;strong&gt;%1 驱动程序&lt;/strong&gt;&lt;br/&gt;由 %2 提供</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="116"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 显卡驱动程序&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;由 %2 提供&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="122"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 浏览器插件&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;由 %2 提供&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="128"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 编解码器&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;由 %2 提供&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="134"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 软件包&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;由 %2 提供&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="140"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;由 %2 提供&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="163"/>
      <source>File: %1</source>
      <translation>文件：%1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Hide license text</source>
      <translation>隐藏协议文本</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Show the license text</source>
      <translation>显示协议文本</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="190"/>
      <source>Open license agreement in browser.</source>
      <translation>在浏览器中打开许可协议。</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <translation>地区：</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <translation>区域：</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change...</source>
      <translation>更改 (&amp;C) ...</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <translation>位置</translation>
    </message>
  </context>
  <context>
    <name>LocaleTests</name>
    <message>
      <location filename="../src/libcalamares/locale/Tests.cpp" line="273"/>
      <source>Quit</source>
      <translation>退出</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="76"/>
      <source>Location</source>
      <translation>位置</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="33"/>
      <source>Configuring LUKS key file.</source>
      <translation>配置 LUKS key 文件。</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="235"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="243"/>
      <source>No partitions are defined.</source>
      <translation>未定义分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="279"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="286"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="300"/>
      <source>Encrypted rootfs setup error</source>
      <translation>加密根文件系时配置错误</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="280"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>根分区%1为LUKS但没有设置密钥。</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="287"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>无法创建根分区%1的LUKS密钥文件。</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="301"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation>无法配置根分区%1的LUKS密钥文件。</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="37"/>
      <source>Generate machine-id.</source>
      <translation>生成 machine-id。</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="53"/>
      <source>Configuration Error</source>
      <translation>配置错误</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="54"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>MachineId未配置根挂载点/</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="237"/>
      <source>Timezone: %1</source>
      <translation>时区: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="258"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <translation>请在地图上选择您的首选位置，安装程序可以为您提供可参考的区域
设置和时区设置。 您可以在下面微调推荐的设置。 拖动以搜索地图，然后
用 +/- 按钮进行放大/缩小，或使用鼠标滚动进行缩放。</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="50"/>
      <source>Package selection</source>
      <translation>软件包选择</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="51"/>
      <source>Office software</source>
      <translation>办公软件</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="52"/>
      <source>Office package</source>
      <translation>办公软件包</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="53"/>
      <source>Browser software</source>
      <translation>浏览器软件</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Browser package</source>
      <translation>浏览器安装包</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Web browser</source>
      <translation>网页浏览器</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Kernel</source>
      <comment>label for netinstall module, Linux kernel</comment>
      <translation>内核</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Services</source>
      <comment>label for netinstall module, system services</comment>
      <translation>服务</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Login</source>
      <comment>label for netinstall module, choose login manager</comment>
      <translation>登录</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Desktop</source>
      <comment>label for netinstall module, choose desktop environment</comment>
      <translation>桌面</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Communication</source>
      <comment>label for netinstall module</comment>
      <translation>通讯</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Development</source>
      <comment>label for netinstall module</comment>
      <translation>开发</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Office</source>
      <comment>label for netinstall module</comment>
      <translation>办公</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Multimedia</source>
      <comment>label for netinstall module</comment>
      <translation>多媒体</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Internet</source>
      <comment>label for netinstall module</comment>
      <translation>互联网</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Theming</source>
      <comment>label for netinstall module</comment>
      <translation>主题化</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Gaming</source>
      <comment>label for netinstall module</comment>
      <translation>游戏</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Utilities</source>
      <comment>label for netinstall module</comment>
      <translation>实用工具</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Applications</source>
      <translation>应用程序</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation>备注</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>批量(&amp;T)：</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;请输入批量标识。它会被保存到目标系统上。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM 配置信息&lt;/h1&gt;&lt;p&gt;Calamares会使用OEM配置信息来配置目标系统。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="122"/>
      <source>OEM Configuration</source>
      <translation>OEM 配置</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="128"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>设置OEM批量标识为 &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="41"/>
      <source>Select your preferred Region, or use the default settings.</source>
      <translation>请选择你偏好打地区或者使用当期默认设置</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="99"/>
      <location filename="../src/modules/localeq/Offline.qml" line="175"/>
      <location filename="../src/modules/localeq/Offline.qml" line="219"/>
      <source>Timezone: %1</source>
      <translation>时区: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="116"/>
      <source>Select your preferred Zone within your Region.</source>
      <translation>在您的区域中选择您的首选区域。</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="188"/>
      <source>Zones</source>
      <translation>区域</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="235"/>
      <source>You can fine-tune Language and Locale settings below.</source>
      <translation>您可以在下面微调“语言”和“区域设置”。</translation>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="51"/>
      <source>Password is too short</source>
      <translation>密码太短</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="67"/>
      <source>Password is too long</source>
      <translation>密码太长</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>Password is too weak</source>
      <translation>密码强度太弱</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>设置“%1”时发生内存分配错误</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="199"/>
      <source>Memory allocation error</source>
      <translation>内存分配错误</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
      <source>The password is the same as the old one</source>
      <translation>新密码和老密码一致</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="203"/>
      <source>The password is a palindrome</source>
      <translation>新密码为回文</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
      <source>The password differs with case changes only</source>
      <translation>新密码和老密码只有大小写区别</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="207"/>
      <source>The password is too similar to the old one</source>
      <translation>新密码和老密码过于相似</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
      <source>The password contains the user name in some form</source>
      <translation>新密码包含用户名</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="211"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>新密码包含用户真实姓名</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
      <source>The password contains forbidden words in some form</source>
      <translation>新密码包含不允许使用的词组</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="221"/>
      <source>The password contains too few digits</source>
      <translation>新密码包含太少数字</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="228"/>
      <source>The password contains too few uppercase letters</source>
      <translation>新密码包含太少大写字母</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="232"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation>
        <numerusform>密码包含的小写字母少于 %n 个</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
      <source>The password contains too few lowercase letters</source>
      <translation>新密码包含太少小写字母</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="242"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>新密码包含太少非字母/数字字符</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="249"/>
      <source>The password is too short</source>
      <translation>新密码过短</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="258"/>
      <source>The password does not contain enough character classes</source>
      <translation>新密码包含太少字符类型</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>新密码包含过多连续的相同字符</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>新密码包含过多连续的同类型字符</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
      <source>The password contains fewer than %n digits</source>
      <translation>
        <numerusform>密码包含的数字少于 %n 个</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation>
        <numerusform>密码包含的大写字母少于 %n 个</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation>
        <numerusform>密码包含的非字母数字字符少于 %n 个</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="246"/>
      <source>The password is shorter than %n characters</source>
      <translation>
        <numerusform>密码少于 %n 个字符</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
      <source>The password is a rotated version of the previous one</source>
      <translation>此密码是上一个的字序调整版本</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
      <source>The password contains fewer than %n character classes</source>
      <translation>
        <numerusform>新密码包含字符类型少于 %n 个</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="262"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation>
        <numerusform>新密码包含超过 %n 个连续的相同字符</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="269"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation>
        <numerusform>新密码包含超过 %n 个连续的同类型字符</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation>
        <numerusform>新密码包含超过 %n 个字符长度的单调序列</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="286"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>新密码包含过长的单调序列</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>No password supplied</source>
      <translation>未输入密码</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="291"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>无法从随机数生成器 (RNG) 设备获取随机数</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>无法生成密码 - 熵值过低</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>新密码无法通过字典检查 - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="301"/>
      <source>The password fails the dictionary check</source>
      <translation>新密码无法通过字典检查</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="305"/>
      <source>Unknown setting - %1</source>
      <translation>未知设置 - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="307"/>
      <source>Unknown setting</source>
      <translation>未知设置</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="311"/>
      <source>Bad integer value of setting - %1</source>
      <translation>设置的整数值非法 - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="313"/>
      <source>Bad integer value</source>
      <translation>设置的整数值非法</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="317"/>
      <source>Setting %1 is not of integer type</source>
      <translation>设定值 %1 不是整数类型</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="319"/>
      <source>Setting is not of integer type</source>
      <translation>设定值不是整数类型</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="323"/>
      <source>Setting %1 is not of string type</source>
      <translation>设定值 %1 不是字符串类型</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="325"/>
      <source>Setting is not of string type</source>
      <translation>设定值不是字符串类型</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="327"/>
      <source>Opening the configuration file failed</source>
      <translation>无法打开配置文件</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="329"/>
      <source>The configuration file is malformed</source>
      <translation>配置文件格式不正确</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="331"/>
      <source>Fatal failure</source>
      <translation>致命错误</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="333"/>
      <source>Unknown error</source>
      <translation>未知错误</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="830"/>
      <source>Password is empty</source>
      <translation>密码是空</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="24"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="50"/>
      <source>Product Name</source>
      <translation>产品名称</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="63"/>
      <source>TextLabel</source>
      <translation>文本标签</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="79"/>
      <source>Long Product Description</source>
      <translation>长产品描述</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation>软件包选择</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>请在列表中选一个产品。被选中的产品将会被安装。</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="205"/>
      <source>Name</source>
      <translation>名称</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="205"/>
      <source>Description</source>
      <translation>描述</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="18"/>
      <source>Form</source>
      <translation>窗体</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard Model:</source>
      <translation>键盘型号：</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="135"/>
      <source>Type here to test your keyboard</source>
      <translation>在此处数据以测试键盘</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="18"/>
      <source>Form</source>
      <translation>窗体</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>您的姓名？</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation>全名</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>您想要使用的登录用户名是？</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation>登录</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>计算机名称为？</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;将计算机设置为对其他网络上计算机可见时将使用此名称。&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation>计算机名称</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>选择一个密码来保证您的账户安全。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;输入相同密码两次，以检查输入错误。好的密码包含字母，数字，标点的组合，应当至少为 8 个字符长，并且应按一定周期更换。&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation>密码</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation>重复密码</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>若选中此项，密码强度检测会开启，你将不被允许使用弱密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation>要求使用强密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>不询问密码自动登录。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>为管理员帐号使用同样的密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>选择管理员账户的密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;输入相同密码两次，以检查输入错误。&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="189"/>
      <source>Root</source>
      <translation>根目录</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
      <source>Home</source>
      <translation>主目录</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="197"/>
      <source>Boot</source>
      <translation>引导</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="202"/>
      <source>EFI system</source>
      <translation>EFI 系统</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="206"/>
      <source>Swap</source>
      <translation>交换</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="210"/>
      <source>New partition for %1</source>
      <translation>%1 的新分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="214"/>
      <source>New partition</source>
      <translation>新建分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="238"/>
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
      <translation>空闲空间</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="161"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="205"/>
      <source>New partition</source>
      <translation>新建分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="298"/>
      <source>Name</source>
      <translation>名称</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="300"/>
      <source>File System</source>
      <translation>文件系统</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="302"/>
      <source>File System Label</source>
      <translation>文件系统卷标</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="304"/>
      <source>Mount Point</source>
      <translation>挂载点</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="306"/>
      <source>Size</source>
      <translation>大小</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="18"/>
      <source>Form</source>
      <translation>窗体</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>存储器(&amp;V)：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>撤销所有修改(&amp;R)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>新建分区表(&amp;T)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>创建</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>编辑(&amp;E)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>删除(&amp;D)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>新分卷组</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>调整分卷组大小</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>停用分卷组</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>移除分卷组</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>安装引导程序至：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="228"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>您是否确定要在 %1 上创建新分区表？</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="263"/>
      <source>Can not create new partition</source>
      <translation>无法创建新分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="264"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>％1上的分区表已经有％2个主分区，并且不能再添加。请删除一个主分区并添加扩展分区。</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="56"/>
      <source>Gathering system information...</source>
      <translation>正在收集系统信息...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="111"/>
      <source>Partitions</source>
      <translation>分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="254"/>
      <source>Unsafe partition actions are enabled.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="257"/>
      <source>Partitioning is configured to &lt;b&gt;always&lt;/b&gt; fail.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="260"/>
      <source>No partitions will be changed.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="300"/>
      <source>Current:</source>
      <translation>当前：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="318"/>
      <source>After:</source>
      <translation>之后：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="529"/>
      <source>No EFI system partition configured</source>
      <translation>未配置 EFI 系统分区</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="533"/>
      <source>EFI system partition configured incorrectly</source>
      <translation>EFI系统分区配置错误</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="538"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a suitable filesystem.</source>
      <translation>启动 %1 必须需要 EFI 系統分区。&lt;br/&gt;&lt;br/&gt;要設定 EFI 系统分区，返回并选择或者建立符合要求的分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="549"/>
      <source>The filesystem must be mounted on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>文件系统必须挂载于 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="555"/>
      <source>The filesystem must have type FAT32.</source>
      <translation>此文件系统必须为FAT32</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="563"/>
      <source>The filesystem must be at least %1 MiB in size.</source>
      <translation>文件系统必须要有%1 MiB 的大小。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="569"/>
      <source>The filesystem must have flag &lt;strong&gt;%1&lt;/strong&gt; set.</source>
      <translation>文件系统必须有 &lt;strong&gt;%1&lt;/strong&gt; 标志设定。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="575"/>
      <source>You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>您可以在不设置EFI系统分区的情况下继续，但您的系統可能无法启动。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="593"/>
      <source>Option to use GPT on BIOS</source>
      <translation>在 BIOS 上使用 GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="594"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;%2&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="626"/>
      <source>Boot partition not encrypted</source>
      <translation>引导分区未加密</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="627"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>您尝试用单独的引导分区配合已加密的根分区使用，但引导分区未加密。&lt;br/&gt;&lt;br/&gt;这种配置方式可能存在安全隐患，因为重要的系统文件存储在了未加密的分区上。&lt;br/&gt;您可以继续保持此配置，但是系统解密将在系统启动时而不是引导时进行。&lt;br/&gt;要加密引导分区，请返回上一步并重新创建此分区，并在分区创建窗口选中 &lt;strong&gt;加密&lt;/strong&gt; 选项。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="718"/>
      <source>has at least one disk device available.</source>
      <translation>有至少一个可用的磁盘设备。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="719"/>
      <source>There are no partitions to install on.</source>
      <translation>无可用于安装的分区。</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>Plasma 外观主题任务</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>无法选中 KDE Plasma 外观主题包</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="79"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>请选择一个 KDE Plasma 桌面外观。你也可以忽略此步骤并在系统安装完成后配置外观。点击外观后可以实时预览效果。</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="84"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>请选择一个 KDE Plasma 桌面外观，可以忽略此步骤并在系统安装完成后配置外观。点击一个外观后可以实时预览效果。</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <translation>外观主题</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="53"/>
      <source>Saving files for later ...</source>
      <translation>保存文件以供日后使用</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="61"/>
      <source>No files configured to save for later.</source>
      <translation>没有已保存且供日后使用的配置文件。</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="85"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>并不是所有配置文件都可以被保留</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="309"/>
      <source>
There was no output from the command.</source>
      <translation>
命令没有输出。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="310"/>
      <source>
Output:
</source>
      <translation>
输出：
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="314"/>
      <source>External command crashed.</source>
      <translation>外部命令已崩溃。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="315"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>命令 &lt;i&gt;%1&lt;/i&gt; 已崩溃。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="320"/>
      <source>External command failed to start.</source>
      <translation>无法启动外部命令。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="321"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>无法启动命令 &lt;i&gt;%1&lt;/i&gt;。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="325"/>
      <source>Internal error when starting command.</source>
      <translation>启动命令时出现内部错误。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="326"/>
      <source>Bad parameters for process job call.</source>
      <translation>呼叫进程任务出现错误参数</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="330"/>
      <source>External command failed to finish.</source>
      <translation>外部命令未成功完成。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="331"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>命令 &lt;i&gt;%1&lt;/i&gt; 未能在 %2 秒内完成。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="338"/>
      <source>External command finished with errors.</source>
      <translation>外部命令已完成，但出现了错误。</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="339"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>命令 &lt;i&gt;%1&lt;/i&gt; 以退出代码 %2 完成。</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/libcalamares/locale/Translation.cpp" line="145"/>
      <source>%1 (%2)</source>
      <translation>%1（%2）</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="33"/>
      <source>unknown</source>
      <translation>未知</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="35"/>
      <source>extended</source>
      <translation>扩展分区</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="37"/>
      <source>unformatted</source>
      <translation>未格式化</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="39"/>
      <source>swap</source>
      <translation>交换分区</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="130"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="167"/>
      <source>Default</source>
      <translation>默认</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="72"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="76"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>File not found</source>
      <translation>找不到文件</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="65"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>路径 &lt;pre&gt;%1&lt;/pre&gt; 必须是绝对路径。</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="83"/>
      <source>Directory not found</source>
      <translation>找不到目录</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="84"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="94"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>无法创建新的随机文件 &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="74"/>
      <source>No product</source>
      <translation>无产品</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="82"/>
      <source>No description provided.</source>
      <translation>未提供描述信息</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="44"/>
      <source>(no mount point)</source>
      <translation>（无挂载点）</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="40"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>尚未分区的空间或分区表未知</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;此计算机不满足安装 %1 的某些推荐配置。&lt;br/&gt;
        安装可以继续，但是一些特性可能被禁用。&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="34"/>
      <source>Remove live user from target system</source>
      <translation>从目标系统删除 live 用户</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="38"/>
      <source>Remove Volume Group named %1.</source>
      <translation>移除分卷组 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="32"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>移除分卷组 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>安装器无法移除分卷组 '%1'。</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="128"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>&lt;b&gt;选择要安装 %1 的地方。&lt;/b&gt;&lt;br/&gt;&lt;font color="red"&gt;警告：&lt;/font&gt;这将会删除所有已选取的分区上的文件。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="150"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>选中项似乎不是有效分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="158"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>无法在空白空间中安装 %1。请选取一个存在的分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>无法在拓展分区上安装 %1。请选取一个存在的主要或逻辑分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>无法安装 %1 到此分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="184"/>
      <source>Data partition (%1)</source>
      <translation>数据分区 (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="204"/>
      <source>Unknown system partition (%1)</source>
      <translation>未知系统分区 (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="208"/>
      <source>%1 system partition (%2)</source>
      <translation>%1 系统分区 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="220"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;分区 %1 对 %2 来说太小了。请选取一个容量至少有 %3 GiB 的分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="242"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;在此系统上找不到任何 EFI 系统分区。请后退到上一步并使用手动分区配置 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="253"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="269"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="294"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;即将安装 %1 到 %2 上。&lt;br/&gt;&lt;font color="red"&gt;警告： &lt;/font&gt;分区 %2 上的所有数据都将丢失。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>将使用 %1 处的 EFI 系统分区启动 %2。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="277"/>
      <source>EFI system partition:</source>
      <translation>EFI 系统分区：</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="38"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation>&lt;p&gt;此计算机不满足安装 %1 的最低配置。&lt;br/&gt;
        安装无法继续。&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;此计算机不满足安装 %1 的某些推荐配置。&lt;br/&gt;
        安装可以继续，但是一些特性可能被禁用。&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="45"/>
      <source>Resize Filesystem Job</source>
      <translation>调整文件系统大小的任务</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="168"/>
      <source>Invalid configuration</source>
      <translation>无效配置</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="169"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>调整文件系统大小的任务 因为配置文件无效不会被执行。</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="174"/>
      <source>KPMCore not Available</source>
      <translation>KPMCore不可用</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="175"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation>Calamares 无法启动 KPMCore来完成调整文件系统大小的任务。</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="183"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="192"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="203"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="212"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="230"/>
      <source>Resize Failed</source>
      <translation>调整大小失败</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="185"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>文件系统 %1 未能在此系统上找到，因此无法调整大小。</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>设备 %1 未能在此系统上找到，因此无法调整大小。</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="194"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="205"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>文件系统 %1 无法被调整大小。</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="206"/>
      <source>The device %1 cannot be resized.</source>
      <translation>设备 %1 无法被调整大小。</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="213"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>文件系统 %1 必须调整大小，但无法做到。</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="214"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>设备 %1 必须调整大小，但无法做到。</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="41"/>
      <source>Resize partition %1.</source>
      <translation>调整分区 %1 大小。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>将 &lt;strong&gt;%2MiB&lt;/strong&gt; 分区的大小从&lt;strong&gt;%1&lt;/strong&gt; 调整至&lt;strong&gt;%3MiB&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="59"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>正将 %2MB 的分区%1调整为 %3MB。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="77"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>安装程序调整磁盘“%2”上的分区 %1 大小失败。</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <translation>调整分卷组大小</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="28"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="46"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>将分卷组%1的大小从%2调整为%3。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>将分卷组&lt;strong&gt;%1&lt;/strong&gt;的大小从&lt;strong&gt;%2&lt;/strong&gt;调整为&lt;strong&gt;%3&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>安装器未能调整分卷组'%1'的大小</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="138"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>为了更好的体验，请确保这台电脑: </translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="139"/>
      <source>System requirements</source>
      <translation>系统需求</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Scanning storage devices...</source>
      <translation>正在扫描存储器…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Partitioning</source>
      <translation>正在分区</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="36"/>
      <source>Set hostname %1</source>
      <translation>设置主机名 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="43"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>设置主机名 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="50"/>
      <source>Setting hostname %1.</source>
      <translation>正在设置主机名 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="124"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="131"/>
      <source>Internal Error</source>
      <translation>内部错误</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="142"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="159"/>
      <source>Cannot write hostname to target system</source>
      <translation>无法向目标系统写入主机名</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="55"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>将键盘型号设置为 %1，布局设置为 %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="368"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>无法将键盘配置写入到虚拟控制台。</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="369"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="397"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="414"/>
      <source>Failed to write to %1</source>
      <translation>写入到 %1 失败</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="396"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>无法为 X11 写入键盘配置。</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="413"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>无法将键盘配置写入到现有的 /etc/default 目录。</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="45"/>
      <source>Set flags on partition %1.</source>
      <translation>设置分区 %1 的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="51"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>设置 %1MB %2 分区的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="55"/>
      <source>Set flags on new partition.</source>
      <translation>设置新分区的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>清空分区 &lt;strong&gt;%1&lt;/strong&gt; 上的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="73"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>删除 %1MB &lt;strong&gt;%2&lt;/strong&gt; 分区的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="77"/>
      <source>Clear flags on new partition.</source>
      <translation>删除新分区的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="82"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>将分区 &lt;strong&gt;%2&lt;/strong&gt; 标记为 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>将 %1MB &lt;strong&gt;%2&lt;/strong&gt; 分区标记为 &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="98"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>将新分区标记为 &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="110"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>正在清理分区 &lt;strong&gt;%1&lt;/strong&gt; 上的标记。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="116"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>正在删除 %1MB &lt;strong&gt;%2&lt;/strong&gt; 分区的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="121"/>
      <source>Clearing flags on new partition.</source>
      <translation>正在删除新分区的标记.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="126"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>正在为分区 &lt;strong&gt;%1&lt;/strong&gt; 设置标记 &lt;strong&gt;%2&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="135"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>正在将 %1MB &lt;strong&gt;%2&lt;/strong&gt; 分区标记为 &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="142"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>正在将新分区标记为 &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="156"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>安装程序没有成功设置分区 %1 的标记.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="40"/>
      <source>Set password for user %1</source>
      <translation>设置用户 %1 的密码</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="47"/>
      <source>Setting password for user %1.</source>
      <translation>正在为用户 %1 设置密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>Bad destination system path.</source>
      <translation>非法的目标系统路径。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="82"/>
      <source>rootMountPoint is %1</source>
      <translation>根挂载点为 %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="88"/>
      <source>Cannot disable root account.</source>
      <translation>无法禁用 root 帐号。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>passwd terminated with error code %1.</source>
      <translation>passwd 以错误代码 %1 终止。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot set password for user %1.</source>
      <translation>无法设置用户 %1 的密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod 以错误代码 %1 中止。</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="34"/>
      <source>Set timezone to %1/%2</source>
      <translation>设置时区为 %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="62"/>
      <source>Cannot access selected timezone path.</source>
      <translation>无法访问指定的时区路径。</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="63"/>
      <source>Bad path: %1</source>
      <translation>非法路径：%1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot set timezone.</source>
      <translation>无法设置时区。</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>链接创建失败，目标：%1，链接名称：%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="77"/>
      <source>Cannot set timezone,</source>
      <translation>无法设置时区，</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="78"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>无法打开要写入的 /etc/timezone</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="182"/>
      <source>Preparing groups.</source>
      <translation>正在准备群组。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="194"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="199"/>
      <source>Could not create groups in target system</source>
      <translation>无法在目标系统中创建群组</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="200"/>
      <source>These groups are missing in the target system: %1</source>
      <translation>目标系统中缺少以下群组: %1</translation>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="34"/>
      <source>Configure &lt;pre&gt;sudo&lt;/pre&gt; users.</source>
      <translation>配置 &lt;pre&gt;sudo&lt;/pre&gt; 用户。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="71"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>无法修改 sudoers 文件权限。</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="76"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>无法创建要写入的 sudoers 文件。</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="40"/>
      <source>Shell Processes Job</source>
      <translation>Shell 进程任务</translation>
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
    <name>StandardButtons</name>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="23"/>
      <source>&amp;OK</source>
      <translation>&amp;确定</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="24"/>
      <source>&amp;Yes</source>
      <translation>&amp;是</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="25"/>
      <source>&amp;No</source>
      <translation>&amp;否</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="26"/>
      <source>&amp;Cancel</source>
      <translation>取消(&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="27"/>
      <source>&amp;Close</source>
      <translation>&amp;关闭</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="101"/>
      <source>Installation feedback</source>
      <translation>安装反馈</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="107"/>
      <source>Sending installation feedback.</source>
      <translation>发送安装反馈。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="125"/>
      <source>Internal error in install-tracking.</source>
      <translation>在 install-tracking 步骤发生内部错误。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="126"/>
      <source>HTTP request timed out.</source>
      <translation>HTTP 请求超时。</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="193"/>
      <source>KDE user feedback</source>
      <translation>KDE 用户反馈</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="199"/>
      <source>Configuring KDE user feedback.</source>
      <translation>配置 KDE 用户反馈。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="221"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="229"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation>KDE 用户反馈配置中存在错误。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="222"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation>无法正确 KDE 用户反馈，脚本错误代码 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="230"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation>无法正确 KDE 用户反馈，Calamares 错误代码 %1。</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="136"/>
      <source>Machine feedback</source>
      <translation>机器反馈</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="142"/>
      <source>Configuring machine feedback.</source>
      <translation>正在配置机器反馈。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="165"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="174"/>
      <source>Error in machine feedback configuration.</source>
      <translation>机器反馈配置中存在错误。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="167"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>无法正确配置机器反馈，脚本错误代码 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="176"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>无法正确配置机器反馈，Calamares 错误代码 %1。</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>占位符</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;单击此处 &lt;span style=" font-weight:600;"&gt;不发送任何&lt;/span&gt; 有关安装的信息。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;点击此处以获取关于用户反馈的详细信息&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="95"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation>跟踪帮助 %1 以查看它的安装频率、安装硬件以及使用的应用程序。请点按每项旁的帮助图标以查看即将被发送的信息。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="100"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation>选中此项时，安装器将发送关于安装过程和硬件的信息。该信息仅会在安装结束后发送&lt;b&gt;一次&lt;/b&gt; 。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="103"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation>通过选择此选项，您将定期将有关您 &lt;b&gt;计算机&lt;/b&gt;的安装，硬件和应用程序的信息发送到 %1。</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="107"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation>通过选择此选项，您将定期将有关&lt;b&gt;用户&lt;/b&gt; 安装，硬件，应用程序和应用程序使用方式的信息发送到 %1。</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <translation>反馈</translation>
    </message>
  </context>
  <context>
    <name>UmountJob</name>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="39"/>
      <source>Unmount file systems.</source>
      <translation>卸载文件系统。</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="124"/>
      <source>No target system available.</source>
      <translation>没有可用的目标系统。</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="132"/>
      <source>No rootMountPoint is set.</source>
      <translation>没有设定 root挂载点。</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="190"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;如果有多人要使用此计算机，您可以在安装后创建多个账户。&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="196"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;如果有多人要使用此计算机，您可以在安装后创建多个账户。&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="35"/>
      <source>Users</source>
      <translation>用户</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>用户</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="232"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation>Key</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="236"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>值</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>创建存储组</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>物理分卷列表：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>分卷组名称：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>分卷组类型：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>物理区域PE大小：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>大小：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>已用空间：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>总扇区数：</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>逻辑分卷数量：</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="18"/>
      <source>Form</source>
      <translation>表单</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation>选择应用程序和系统语言</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>&amp;About</source>
      <translation>关于(&amp;A)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="150"/>
      <source>Open donations website</source>
      <translation>打开捐赠信息网页</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>&amp;Donate</source>
      <translation>捐赠(&amp;D)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="163"/>
      <source>Open help and support website</source>
      <translation>打开帮助和支持页面</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>&amp;Support</source>
      <translation>支持信息(&amp;S)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
      <source>Open issues and bug-tracking website</source>
      <translation>打开问题追踪网站</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>&amp;Known issues</source>
      <translation>已知问题(&amp;K)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="189"/>
      <source>Open release notes website</source>
      <translation>打开发布日志网页</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="192"/>
      <source>&amp;Release notes</source>
      <translation>发行注记(&amp;R)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="216"/>
      <source>%1 support</source>
      <translation>%1 的支持信息</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="223"/>
      <source>About %1 setup</source>
      <translation>关于 %1 安装程序</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="223"/>
      <source>About %1 installer</source>
      <translation>关于 %1 安装程序</translation>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="40"/>
      <source>Welcome</source>
      <translation>欢迎</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="46"/>
      <source>Welcome</source>
      <translation>欢迎</translation>
    </message>
  </context>
  <context>
    <name>ZfsJob</name>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="101"/>
      <source>Create ZFS pools and datasets</source>
      <translation>创建 ZFS 池和数据集</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="162"/>
      <source>Failed to create zpool on </source>
      <translation>创建 zpool 失败于</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="180"/>
      <source>Configuration Error</source>
      <translation>配置错误</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="181"/>
      <source>No partitions are available for ZFS.</source>
      <translation>没有可用于 ZFS 的分区。</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <source>Internal data missing</source>
      <translation>内部数据丢失</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="257"/>
      <source>Failed to create zpool</source>
      <translation>创建 zpool 失败</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="329"/>
      <source>Failed to create dataset</source>
      <translation>创建数据集失败</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="330"/>
      <source>The output was: </source>
      <translation>输出为：</translation>
    </message>
  </context>
  <context>
    <name>about</name>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="79"/>
      <source>Back</source>
      <translation>后退</translation>
    </message>
  </context>
  <context>
    <name>calamares-sidebar</name>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="79"/>
      <source>Show debug information</source>
      <translation>显示调试信息</translation>
    </message>
  </context>
  <context>
    <name>finishedq</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="36"/>
      <source>Installation Completed</source>
      <translation>安装完成</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <translation>%1 已安装在您的电脑上了。&lt;br/&gt;
         您现在可以重新启动到新系统，或是继续使用 Live 环境。</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="65"/>
      <source>Close Installer</source>
      <translation>关闭安装程序</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="71"/>
      <source>Restart System</source>
      <translation>重启系统</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <translation>安装过程中的翻译已经复制到了临时用户的家目录下
于此同时安装日志也已经复制到了目标系统，路径为：/var/log/installation.log</translation>
    </message>
  </context>
  <context>
    <name>finishedq@mobile</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="36"/>
      <source>Installation Completed</source>
      <translation>安装完成</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart your device.</source>
      <translation>%1 已安装在您的计算机上。&lt;br/&gt;
  现在可以重新启动设备了。</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="65"/>
      <source>Close</source>
      <translation>关闭</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="71"/>
      <source>Restart</source>
      <translation>重启</translation>
    </message>
  </context>
  <context>
    <name>i18n</name>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="50"/>
      <source>&lt;h1&gt;Languages&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;语言&lt;/h1&gt; &lt;/br&gt;
                   系统语言区域设置会影响部份命令行用户界面的语言及字符集。 当前设置是 &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="123"/>
      <source>&lt;h1&gt;Locales&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;区域&lt;/h1&gt; &lt;/br&gt;
                    系统区域设置会影响数字和日期格式。 当前设置是 &lt;strong&gt;%1&lt;/strong&gt;。</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="189"/>
      <source>Back</source>
      <translation>后退</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="60"/>
      <source>To activate keyboard preview, select a layout.</source>
      <translation>要启用键盘预览，请选择一个键盘布局</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="86"/>
      <source>Keyboard Model:</source>
      <translation>键盘型号：</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="256"/>
      <source>Layouts</source>
      <translation>布局</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="265"/>
      <source>Type here to test your keyboard</source>
      <translation>在此处数据以测试键盘</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="180"/>
      <source>Variants</source>
      <translation>变体</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="81"/>
      <source>Change</source>
      <translation>更改</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
&lt;p&gt;这些是发布日志样例&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>packagechooserq</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice 是強大且自由的辦办公软件，世界上有百万级别的用户量。其中包括多种组件模块使其成为世界上最强大的开源并自由的办公软件。&lt;br/&gt;
                    预设选项。</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>如果你不想安装办公软件，请选择不安装办公软件的选项即可。稍后您可以在安装好的系统上根据个人喜好自行选择安装办公软件与否。您可以随时在安装好的系统上添加一个（或多个）办公软件。</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>无办公软件</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation>建立最小化的桌面安装，移除所有的附加应用。在稍后自行选择需要安装至系统的应用。同时不会有任何的模板和例子可供选择。无办公软件，无媒体播放器，无图片查看器或者打印支持。仅仅有一个桌面，文件管理器，包管理器，文本编辑器和一个网页浏览器。</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>最小化安装</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation>请为你的安装指定一个选项，或者使用默认选项：安装LibreOffice</translation>
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
            &lt;p&gt;这是一个QML 示例文件，显示了具有 Flickable 内容的 RichText 选项。&lt;/p&gt;

            &lt;p&gt;带有 RichText 的 QML 可以使用 HTML 标签，
  Flickable 内容对于触摸屏很有用。&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;这是粗体字&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;这是斜体字&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;&lt;u&gt;这是带下划线的文字&lt;/u&gt;&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;此文本将居中对齐。&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;这是删除线&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;代码示例:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;列表:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;Intel CPU 系统&lt;/li&gt;
                &lt;li&gt;AMD CPU 系统&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;垂直滚动条是可调的，当前宽度设置为10。&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="76"/>
      <source>Back</source>
      <translation>后退</translation>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="43"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>选择您的用户名和凭据登录并执行管理任务</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="56"/>
      <source>What is your name?</source>
      <translation>您的姓名？</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="63"/>
      <source>Your Full Name</source>
      <translation>全名</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>您想要使用的登录用户名是？</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login Name</source>
      <translation>登录名</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="116"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>如果有多人要使用此计算机，您可以在安装后创建多个账户。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="129"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>只允许小写字母、数组、下划线"_" 和 连字符"-"</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="138"/>
      <source>root is not allowed as username.</source>
      <translation>用户名不能为root</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="147"/>
      <source>What is the name of this computer?</source>
      <translation>计算机名称为？</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="153"/>
      <source>Computer Name</source>
      <translation>计算机名称</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="180"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>将计算机设置为对其他网络上计算机可见时将使用此名称。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="202"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost不能为用户名</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="211"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>选择一个密码来保证您的账户安全。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="221"/>
      <source>Password</source>
      <translation>密码</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="238"/>
      <source>Repeat Password</source>
      <translation>重复密码</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="265"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>输入相同密码两次，以检查输入错误。好的密码包含字母，数字，标点的组合，应当至少为 8 个字符长，并且应按一定周期更换。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="410"/>
      <source>Validate passwords quality</source>
      <translation>验证密码质量</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="420"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>若选中此项，密码强度检测会开启，你将不被允许使用弱密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="402"/>
      <source>Log in automatically without asking for the password</source>
      <translation>不询问密码自动登录</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="193"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>只允许字母、数组、下划线"_" 和 连字符"-"，最少两个字符。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="297"/>
      <source>Reuse user password as root password</source>
      <translation>重用用户密码作为 root 密码</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="305"/>
      <source>Use the same password for the administrator account.</source>
      <translation>为管理员帐号使用同样的密码。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>选择一个 root 密码来保证您的账户安全。</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="328"/>
      <source>Root Password</source>
      <translation>Root 密码</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="346"/>
      <source>Repeat Root Password</source>
      <translation>重复 Root 密码</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="372"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>输入相同密码两次，以检查输入错误。</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="35"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;欢迎来到  %1 &lt;quote&gt;%2&lt;/quote&gt; 安装程序&lt;/h3&gt;
            &lt;p&gt;这个程序将询问您一些问题并在您的计算机上安装 %1。&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="66"/>
      <source>About</source>
      <translation>关于</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Support</source>
      <translation>支持</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Known issues</source>
      <translation>已知问题</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="102"/>
      <source>Release notes</source>
      <translation>发行说明</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="114"/>
      <source>Donate</source>
      <translation>捐赠</translation>
    </message>
  </context>
</TS>

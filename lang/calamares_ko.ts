<?xml version="1.0" ?><!DOCTYPE TS><TS language="ko" version="2.1">
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="69"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation>이 시스템의 &lt;strong&gt;부트 환경&lt;/strong&gt;입니다. &lt;br&gt; &lt;br&gt; 오래된 x86 시스템은 &lt;strong&gt;BIOS&lt;/strong&gt;만을 지원합니다. &lt;br&gt; 최근 시스템은 주로 &lt;strong&gt;EFI&lt;/strong&gt;을(를) 사용하지만, 호환 모드로 시작한 경우 BIOS로 나타날 수도 있습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="79"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation>이 시스템은 &lt;strong&gt;EFI&lt;/strong&gt; 부트 환경에서 시동되었습니다. &lt;br&gt; &lt;br&gt; EFI 환경에서의 시동에 대해 설정하려면, &lt;strong&gt;EFI 시스템 파티션&lt;/strong&gt;에 &lt;strong&gt;GRUB&lt;/strong&gt;나 &lt;strong&gt;systemd-boot&lt;/strong&gt;와 같은 부트 로더 애플리케이션을 배치해야 합니다. 이 과정은 자동으로 진행됩니다. 단, 수동 파티셔닝을 선택할 경우, EFI 시스템 파티션을 직접 선택 또는 작성해야 합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="91"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation>이 시스템은 &lt;strong&gt;BIOS 부트 환경&lt;/strong&gt;에서 시동되었습니다. &lt;br&gt; &lt;br&gt; BIOS 환경에서의 시동에 대해 설정하려면, 파티션의 시작 위치 또는 파티션 테이블의 시작 위치 근처(권장)에 있는 &lt;strong&gt;마스터 부트 레코드&lt;/strong&gt;에 &lt;strong&gt;GRUB&lt;/strong&gt;과 같은 부트 로더를 설치해야 합니다. 이 과정은 자동으로 진행됩니다. 단, 수동 파티셔닝을 선택할 경우, 사용자가 직접 설정을 해야 합니다.</translation>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation>%1의 마스터 부트 레코드</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>부트 파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>시스템 파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation>부트로더를 설치하지 않습니다</translation>
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
        <translation>빈 페이지</translation>
    </message>
</context>
<context>
    <name>Calamares::DebugWindow</name>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="24"/>
        <source>GlobalStorage</source>
        <translation>전역 스토리지</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation>작업 대기열</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation>모듈</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Type:</source>
        <translation>유형:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="64"/>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="78"/>
        <source>none</source>
        <translation>없음</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="71"/>
        <source>Interface:</source>
        <translation>인터페이스:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="93"/>
        <source>Tools</source>
        <translation>도구</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="182"/>
        <source>Debug information</source>
        <translation>디버깅 정보</translation>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="79"/>
        <source>Install</source>
        <translation>설치</translation>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="101"/>
        <source>Done</source>
        <translation>완료</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
        <source>Run command %1 %2</source>
        <translation>커맨드 %1 %2 실행</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="61"/>
        <source>Running command %1 %2</source>
        <translation>커맨드 %1 %2 실행 중</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="273"/>
        <source>Running %1 operation.</source>
        <translation>%1 명령을 실행 중</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="288"/>
        <source>Bad working directory path</source>
        <translation>잘못된 작업 디렉터리 경로</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="289"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>파이썬 작업 %2에 대한 작업 디렉터리 %1을 읽을 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="299"/>
        <source>Bad main script file</source>
        <translation>잘못된 주 스크립트 파일</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="300"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>파이썬 작업 %2에 대한 주 스크립트 파일 %1을 읽을 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="376"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>작업 &quot;%1&quot;에서 Boost.Python 오류</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="74"/>
        <source>&amp;Back</source>
        <translation>뒤로(&amp;B)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="75"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="279"/>
        <source>&amp;Next</source>
        <translation>다음(&amp;N)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="76"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="288"/>
        <source>&amp;Cancel</source>
        <translation>취소(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="77"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="289"/>
        <source>Cancel installation without changing the system.</source>
        <translation>시스템 변경 없이 설치를 취소합니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="179"/>
        <source>Calamares Initialization Failed</source>
        <translation>Calamares 초기화 실패</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="180"/>
        <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
        <translation>%1 이(가) 설치될 수 없습니다. Calamares가 모든 구성된 모듈을 불러올 수 없었습니다. 이것은 Calamares가 분포에 의해 사용되는 방식에서 비롯된 문제입니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="185"/>
        <source>&lt;br/&gt;The following modules could not be loaded:</source>
        <translation>다음 모듈 불러오기 실패:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="277"/>
        <source>&amp;Install</source>
        <translation>설치(&amp;I)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="325"/>
        <source>Cancel installation?</source>
        <translation>설치를 취소하시겠습니까?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="326"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>정말로 현재 설치 프로세스를 취소하시겠습니까?
설치 관리자가 종료되며 모든 변경은 반영되지 않습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="331"/>
        <source>&amp;Yes</source>
        <translation>예(&amp;Y)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
        <source>&amp;No</source>
        <translation>아니오(&amp;N)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="163"/>
        <source>&amp;Close</source>
        <translation>닫기(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="237"/>
        <source>Continue with setup?</source>
        <translation>설치를 계속하시겠습니까?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="238"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation>%1 인스톨러가 %2를 설치하기 위해 사용자의 디스크의 내용을 변경하려고 합니다. &lt;br/&gt; &lt;strong&gt;이 변경 작업은 되돌릴 수 없습니다.&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="243"/>
        <source>&amp;Install now</source>
        <translation>지금 설치(&amp;I)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="244"/>
        <source>Go &amp;back</source>
        <translation>뒤로 이동(&amp;b)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="283"/>
        <source>&amp;Done</source>
        <translation>완료(&amp;D)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="284"/>
        <source>The installation is complete. Close the installer.</source>
        <translation>설치가 완료되었습니다. 설치 관리자를 닫습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
        <source>Error</source>
        <translation>오류</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="161"/>
        <source>Installation Failed</source>
        <translation>설치 실패</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="270"/>
        <source>Unknown exception type</source>
        <translation>알 수 없는 예외 유형</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="284"/>
        <source>unparseable Python error</source>
        <translation>구문 분석할 수 없는 파이썬 오류</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="324"/>
        <source>unparseable Python traceback</source>
        <translation>구문 분석할 수 없는 파이썬 역추적 정보</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="329"/>
        <source>Unfetchable Python error.</source>
        <translation>가져올 수 없는 파이썬 오류</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="44"/>
        <source>%1 Installer</source>
        <translation>%1 설치 관리자</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="111"/>
        <source>Show debug information</source>
        <translation>디버깅 정보 보기</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="96"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="151"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="174"/>
        <source>For best results, please ensure that this computer:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="202"/>
        <source>System requirements</source>
        <translation>시스템 요구 사항</translation>
    </message>
</context>
<context>
    <name>ChoicePage</name>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="131"/>
        <source>After:</source>
        <translation>이후:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="238"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1001"/>
        <source>Boot loader location:</source>
        <translation>부트 로더 위치:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="945"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="129"/>
        <source>Select storage de&amp;vice:</source>
        <translation>스토리지 장치 선택</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="130"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="927"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="973"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1052"/>
        <source>Current:</source>
        <translation>현재:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="798"/>
        <source>Reuse %1 as home partition for %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="928"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1043"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1099"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1108"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>%1의 EFI 시스템 파티션은 %2의 시작으로 사용될 것입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1116"/>
        <source>EFI system partition:</source>
        <translation>EFI 시스템 파티션:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1232"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1237"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1274"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1296"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1320"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1264"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1241"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1270"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1292"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1316"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1245"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1279"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1300"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1324"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1287"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1311"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="46"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation>파티셔닝 작업을 위해 %1의 마운트를 모두 해제합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="54"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation>파티셔닝 작업을 위해 %1의 마운트를 모두 해제하는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="191"/>
        <source>Cleared all mounts for %1</source>
        <translation>%1의 모든 마운트가 해제되었습니다.</translation>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
        <source>Clear all temporary mounts.</source>
        <translation>모든 임시 마운트들을 해제합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
        <source>Clearing all temporary mounts.</source>
        <translation>모든 임시 마운트들이 해제하는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation>임시 마운트들의 목록을 가져올 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
        <source>Cleared all temporary mounts.</source>
        <translation>모든 임시 마운트들이 해제되었습니다.</translation>
    </message>
</context>
<context>
    <name>CommandList</name>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="127"/>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="138"/>
        <source>Could not run command.</source>
        <translation>명령을 실행할 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="128"/>
        <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
        <translation>이 명령은 호스트 환경에서 실행되며 루트 경로를 알아야하지만, rootMountPoint가 정의되지 않았습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="139"/>
        <source>The command needs to know the user&apos;s name, but no username is defined.</source>
        <translation>이 명령은 사용자 이름을 알아야 하지만, username이 정의되지 않았습니다.</translation>
    </message>
</context>
<context>
    <name>ContextualProcessJob</name>
    <message>
        <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="117"/>
        <source>Contextual Processes Job</source>
        <translation>컨텍스트 프로세스 작업</translation>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>파티션 생성</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
        <source> MiB</source>
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
        <source>Partition &amp;Type:</source>
        <translation>파티션 유형(&amp;T):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
        <source>&amp;Primary</source>
        <translation>주 파티션(&amp;P)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
        <source>E&amp;xtended</source>
        <translation>확장 파티션(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
        <source>Fi&amp;le System:</source>
        <translation>파일 시스템(&amp;l):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
        <source>LVM LV name</source>
        <translation>LVM 논리 볼륨 이름</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
        <source>Flags:</source>
        <translation>플래그:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
        <source>&amp;Mount Point:</source>
        <translation>마운트 지점(&amp;M):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Si&amp;ze:</source>
        <translation>크기(&amp;z):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="72"/>
        <source>En&amp;crypt</source>
        <translation>암호화(&amp;c)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="151"/>
        <source>Logical</source>
        <translation>논리 파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="156"/>
        <source>Primary</source>
        <translation>주 파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="173"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="262"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>마운트 위치가 이미 사용 중입니다. 다른 위치를 선택해주세요.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="44"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="55"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="67"/>
        <source>Creating new %1 partition on %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="79"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>파티션 테이블을 만듭니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>새로운 파티션 테이블의 생성은 디스크에 있는 모든 데이터를 지울 것입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>만들고자 하는 파티션 테이블의 종류는 무엇인가요?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
        <source>Master Boot Record (MBR)</source>
        <translation>마스터 부트 레코드 (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
        <source>GUID Partition Table (GPT)</source>
        <translation>GUID 파티션 테이블 (GPT)</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
        <source>Create new %1 partition table on %2.</source>
        <translation>%2에 %1 파티션 테이블을 만듭니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="54"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt;에 새로운 &lt;strong&gt;%1&lt;/strong&gt; 파티션 테이블을 만듭니다 (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="64"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation>%2에 새로운 %1 파티션 테이블을 만드는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="82"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>설치 관리자가 %1에 파티션 테이블을 만들지 못했습니다.</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
        <source>Create user %1</source>
        <translation>%1 사용자를 만듭니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt;사용자를 만듭니다 .</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
        <source>Creating user %1.</source>
        <translation>%1 사용자를 만드는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="81"/>
        <source>Sudoers dir is not writable.</source>
        <translation>Sudoers 디렉터리가 쓰기 금지되어 있습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="85"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>sudoers 파일을 만들 수가 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="93"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>sudoers 파일의 권한을 변경할 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="99"/>
        <source>Cannot open groups file for reading.</source>
        <translation>groups 파일을 읽을 수가 없습니다.</translation>
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
        <source>The installer failed to create a volume group named &apos;%1&apos;.</source>
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
        <translation>%1 파티션을 지웁니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="48"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt; 파티션을 지웁니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
        <source>Deleting partition %1.</source>
        <translation>%1 파티션을 지우는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>설치 관리자가 %1 파티션을 지우지 못했습니다.</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="150"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation>이 장치는 &lt;strong&gt;%1&lt;/strong&gt; 파티션 테이블을 갖고 있습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation type="unfinished"/>
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
        <location filename="../src/modules/partition/core/DeviceModel.cpp" line="83"/>
        <source>%1 - %2 (%3)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/core/DeviceModel.cpp" line="89"/>
        <source>%1 - (%2)</source>
        <translation type="unfinished"/>
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
        <translation>%1을 열지 못했습니다</translation>
    </message>
</context>
<context>
    <name>DummyCppJob</name>
    <message>
        <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="47"/>
        <source>Dummy C++ Job</source>
        <translation>더미 C++ 작업</translation>
    </message>
</context>
<context>
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>기존 파티션을 수정합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>내용:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation>유지(&amp;K)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>포맷</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>경고: 파티션을 포맷하는 것은 모든 데이터를 지울 것입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>마운트 위치(&amp;M):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation>크기(&amp;z):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
        <source> MiB</source>
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
        <source>Fi&amp;le System:</source>
        <translation>파일 시스템(&amp;l):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
        <source>Flags:</source>
        <translation>플래그:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="269"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>마운트 위치가 이미 사용 중입니다. 다른 위치를 선택해주세요.</translation>
    </message>
</context>
<context>
    <name>EncryptWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
        <source>En&amp;crypt system</source>
        <translation>시스템 암호화(&amp;c)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
        <source>Passphrase</source>
        <translation>암호</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
        <source>Confirm passphrase</source>
        <translation>암호 확인</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
        <source>Please enter the same passphrase in both boxes.</source>
        <translation>암호와 암호 확인 상자에 동일한 값을 입력해주세요.</translation>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="132"/>
        <source>Set partition information</source>
        <translation>파티션 정보 설정</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="156"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="160"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="168"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="173"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="185"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="195"/>
        <source>Setting up mount points.</source>
        <translation>마운트 위치를 설정 중입니다.</translation>
    </message>
</context>
<context>
    <name>FinishedPage</name>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="95"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style=&quot; font-style:italic;&quot;&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
        <source>&amp;Restart now</source>
        <translation>지금 재시작(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="51"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="109"/>
        <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="59"/>
        <source>Finish</source>
        <translation>완료</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="124"/>
        <source>Installation Complete</source>
        <translation>설치 완료</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
        <source>The installation of %1 is complete.</source>
        <translation>%1의 설치가 완료되었습니다.</translation>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="41"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="52"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation>%1 파티션을 %2 파일 시스템으로 포맷하는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="77"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>설치 관리자가 &apos;%2&apos; 디스크에 있는 %1 파티션을 포맷하지 못했습니다.</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
        <source>Konsole not installed</source>
        <translation>Konsole이 설치되지 않았음</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
        <source>Please install KDE Konsole and try again!</source>
        <translation>KDE Konsole을 설치한 후에 다시 시도해주세요!</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation>스크립트 실행: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation>스크립트</translation>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="219"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>키보드 모델을 %1로 설정합니다.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="221"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>키보드 레이아웃을 %1/%2로 설정합니다.</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
        <source>Keyboard</source>
        <translation>키보드</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="34"/>
        <source>System locale setting</source>
        <translation>시스템 로케일 설정</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="41"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="66"/>
        <source>&amp;Cancel</source>
        <translation>취소(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="67"/>
        <source>&amp;OK</source>
        <translation>확인(&amp;O)</translation>
    </message>
</context>
<context>
    <name>LicensePage</name>
    <message>
        <location filename="../src/modules/license/LicensePage.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="89"/>
        <source>I accept the terms and conditions above.</source>
        <translation>상기 계약 조건을 모두 동의합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="116"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation>&lt;h1&gt;라이센스 동의&lt;/h1&gt;이 설치 절차는 라이센스 조항의 적용을 받는 독점 소프트웨어를 설치합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="119"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation>상기 최종 사용자 라이센스 동의 (EULAs) 를 검토해주시길 바랍니다.&lt;br/&gt;조건에 동의하지 않는다면, 설치 절차를 계속할 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="125"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation>&lt;h1&gt;라이센스 동의&lt;/h1&gt;이 설치 절차는 추가적인 기능들을 제공하고 사용자 환경을 개선하기 위한 독점 소프트웨어를 설치할 수 있으며, 이 소프트웨어는 라이센스 조항의 적용을 받습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="130"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation>상기 최종 사용자 라이센스 동의 (EULAs) 를 검토해주시길 바랍니다. &lt;br/&gt;조건에 동의하지 않는다면, 독점 소프트웨어는 설치되지 않을 것이며, 대체하여 사용할 수 있는 오픈 소스 소프트웨어가 사용될 것입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="160"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="167"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="173"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="179"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="185"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="191"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="203"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation>&lt;a href=&quot;%1&quot;&gt;라이센스 동의 보기&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation>라이센스</translation>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="387"/>
        <source>The system language will be set to %1.</source>
        <translation>시스템 언어가 %1로 설정될 것입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="389"/>
        <source>The numbers and dates locale will be set to %1.</source>
        <translation>숫자와 날짜 로케일이 %1로 설정될 것입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="215"/>
        <source>Region:</source>
        <translation>대륙:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="216"/>
        <source>Zone:</source>
        <translation>표준시간대:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="220"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="221"/>
        <source>&amp;Change...</source>
        <translation>변경(&amp;C)...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="398"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>표준시간대를 %1/%2로 설정합니다.&lt;br/&gt;</translation>
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
        <translation>위치 정보를 불러오는 중입니다...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="175"/>
        <source>Location</source>
        <translation>위치</translation>
    </message>
</context>
<context>
    <name>NetInstallPage</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="64"/>
        <source>Name</source>
        <translation>이름</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="65"/>
        <source>Description</source>
        <translation>설명</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="86"/>
        <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
        <translation>네트워크 설치. (불가: 패키지 목록을 가져올 수 없습니다. 네트워크 연결을 확인해주세요)</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="96"/>
        <source>Network Installation. (Disabled: Received invalid groups data)</source>
        <translation>네트워크 설치. (불가: 유효하지 않은 그룹 데이터를 수신했습니다)</translation>
    </message>
</context>
<context>
    <name>NetInstallViewStep</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
        <source>Package selection</source>
        <translation>패키지 선택</translation>
    </message>
</context>
<context>
    <name>PWQ</name>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="63"/>
        <source>Password is too short</source>
        <translation>암호가 너무 짧습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="85"/>
        <source>Password is too long</source>
        <translation>암호가 너무 깁니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="151"/>
        <source>Password is too weak</source>
        <translation>암호가 너무 취약합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="158"/>
        <source>Memory allocation error when setting &apos;%1&apos;</source>
        <translation>&apos;%1&apos;을 설정하는 중 메모리 할당 오류</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
        <source>Memory allocation error</source>
        <translation>메모리 할당 오류</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
        <source>The password is the same as the old one</source>
        <translation>암호가 이전과 같습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
        <source>The password is a palindrome</source>
        <translation>암호가 회문입니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
        <source>The password differs with case changes only</source>
        <translation>암호가 대소문자만 다릅니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
        <source>The password is too similar to the old one</source>
        <translation>암호가 이전 암호와 너무 유사합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
        <source>The password contains the user name in some form</source>
        <translation>암호가 사용자 이름의 일부를 포함하고 있습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
        <source>The password contains words from the real name of the user in some form</source>
        <translation>암호가 사용자 실명의 일부를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="176"/>
        <source>The password contains forbidden words in some form</source>
        <translation>암호가 금지된 단어를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="179"/>
        <source>The password contains less than %1 digits</source>
        <translation>암호가 %1개 미만의 숫자를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="180"/>
        <source>The password contains too few digits</source>
        <translation>암호가 너무 적은 개수의 숫자들을 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="183"/>
        <source>The password contains less than %1 uppercase letters</source>
        <translation>암호가 %1개 미만의 대문자를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
        <source>The password contains too few uppercase letters</source>
        <translation>암호가 너무 적은 개수의 대문자를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="187"/>
        <source>The password contains less than %1 lowercase letters</source>
        <translation>암호가 %1개 미만의 소문자를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
        <source>The password contains too few lowercase letters</source>
        <translation>암호가 너무 적은 개수의 소문자를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
        <source>The password contains less than %1 non-alphanumeric characters</source>
        <translation>암호가 %1개 미만의 영숫자가 아닌 문자를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="192"/>
        <source>The password contains too few non-alphanumeric characters</source>
        <translation>암호가 너무 적은 개수의 영숫자가 아닌 문자를 포함하고 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
        <source>The password is shorter than %1 characters</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
        <source>The password is too short</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
        <source>The password is just rotated old one</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
        <source>The password contains less than %1 character classes</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
        <source>The password does not contain enough character classes</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
        <source>The password contains more than %1 same characters consecutively</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
        <source>The password contains too many same characters consecutively</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
        <source>The password contains more than %1 characters of the same class consecutively</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
        <source>The password contains too many characters of the same class consecutively</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
        <source>The password contains monotonic sequence longer than %1 characters</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
        <source>The password contains too long of a monotonic character sequence</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="216"/>
        <source>No password supplied</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
        <source>Cannot obtain random numbers from the RNG device</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="220"/>
        <source>Password generation failed - required entropy too low for settings</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
        <source>The password fails the dictionary check - %1</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="227"/>
        <source>The password fails the dictionary check</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="231"/>
        <source>Unknown setting - %1</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
        <source>Unknown setting</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
        <source>Bad integer value of setting - %1</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
        <source>Bad integer value</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
        <source>Setting %1 is not of integer type</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
        <source>Setting is not of integer type</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
        <source>Setting %1 is not of string type</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="259"/>
        <source>Setting is not of string type</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="261"/>
        <source>Opening the configuration file failed</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
        <source>The configuration file is malformed</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
        <source>Fatal failure</source>
        <translation>치명적인 실패</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
        <source>Unknown error</source>
        <translation>알 수 없는 오류</translation>
    </message>
</context>
<context>
    <name>Page_Keyboard</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
        <source>Keyboard Model:</source>
        <translation>키보드 모델:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>키보드를 테스트하기 위해 여기에 입력하세요</translation>
    </message>
</context>
<context>
    <name>Page_UserSetup</name>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
        <source>What is your name?</source>
        <translation>이름이 무엇인가요?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>로그인을 위해 어떤 이름을 사용할 것인가요?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;한명 이상의 사용자가 이 컴퓨터를 사용할 것이라면, 설치 후에 여러 사용자 계정을 설정할 수 있습니다.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>사용자 계정의 보안을 유지하기 위한 암호를 선택하세요.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>이 컴퓨터의 이름은 무엇인가요?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation>암호를 묻지 않고 자동으로 로그인합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation>관리자 계정에 대해 같은 암호를 사용합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>관리자 계정을 위한 암호를 선택하세요.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;입력 오류를 검사하기 위해 암호를 똑같이 두번 입력하세요.&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
        <source>Root</source>
        <translation>루트</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Home</source>
        <translation>홈</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
        <source>Boot</source>
        <translation>부트</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>EFI system</source>
        <translation>EFI 시스템</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>Swap</source>
        <translation>스왑</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
        <source>New partition for %1</source>
        <translation>%1에 대한 새로운 파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
        <source>New partition</source>
        <translation>새로운 파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="224"/>
        <source>%1  %2</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>PartitionModel</name>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="138"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="170"/>
        <source>Free Space</source>
        <translation>여유 공간</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="142"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="174"/>
        <source>New partition</source>
        <translation>새로운 파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="258"/>
        <source>Name</source>
        <translation>이름</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="260"/>
        <source>File System</source>
        <translation>파일 시스템</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="262"/>
        <source>Mount Point</source>
        <translation>마운트 위치</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="264"/>
        <source>Size</source>
        <translation>크기</translation>
    </message>
</context>
<context>
    <name>PartitionPage</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
        <source>Storage de&amp;vice:</source>
        <translation>스토리지 장치(&amp;v):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>모든 변경 되돌리기(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
        <source>New Partition &amp;Table</source>
        <translation>새로운 파티션 테이블(&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
        <source>Cre&amp;ate</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
        <source>&amp;Edit</source>
        <translation>수정(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
        <source>&amp;Delete</source>
        <translation>삭제(&amp;D)</translation>
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
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="217"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="241"/>
        <source>Can not create new partition</source>
        <translation>새로운 파티션을 만들 수 없습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="242"/>
        <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="71"/>
        <source>Gathering system information...</source>
        <translation>시스템 정보 수집 중...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="122"/>
        <source>Partitions</source>
        <translation>파티션</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="159"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="163"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="172"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="185"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="191"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="197"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="204"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="212"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="240"/>
        <source>Current:</source>
        <translation>현재:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="257"/>
        <source>After:</source>
        <translation>이후:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="400"/>
        <source>No EFI system partition configured</source>
        <translation>EFI 시스템 파티션이 설정되지 않았습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="401"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="414"/>
        <source>EFI system partition flag not set</source>
        <translation>EFI 시스템 파티션 플래그가 설정되지 않았습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="415"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="450"/>
        <source>Boot partition not encrypted</source>
        <translation>부트 파티션이 암호화되지 않았습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="451"/>
        <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>PlasmaLnfJob</name>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
        <source>Plasma Look-and-Feel Job</source>
        <translation>플라즈마 Look-and-Feel 작업</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
        <source>Could not select KDE Plasma Look-and-Feel package</source>
        <translation>KDE 플라즈마 Look-and-Feel 패키지를 선택할 수 없습니다</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfPage</name>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="20"/>
        <source>Placeholder</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="67"/>
        <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
        <translation type="unfinished"/>
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
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="85"/>
        <source>Saving files for later ...</source>
        <translation>나중을 위해 파일들을 저장하는 중...</translation>
    </message>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="123"/>
        <source>No files configured to save for later.</source>
        <translation>나중을 위해 저장될 설정된 파일들이 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="177"/>
        <source>Not all of the configured files could be preserved.</source>
        <translation>모든 설정된 파일들이 보존되는 것은 아닙니다.</translation>
    </message>
</context>
<context>
    <name>ProcessResult</name>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="271"/>
        <source>
There was no output from the command.</source>
        <translation>
명령으로부터 아무런 출력이 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="272"/>
        <source>
Output:
</source>
        <translation>
출력:
</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="275"/>
        <source>External command crashed.</source>
        <translation>외부 명령이 실패했습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="276"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
        <translation>&lt;i&gt;%1&lt;/i&gt; 명령이 실패했습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="281"/>
        <source>External command failed to start.</source>
        <translation>외부 명령을 시작하지 못했습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="282"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
        <translation>&lt;i&gt;%1&lt;/i&gt; 명령을 시작하지 못했습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="286"/>
        <source>Internal error when starting command.</source>
        <translation>명령을 시작하는 중에 내부 오류가 발생했습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="287"/>
        <source>Bad parameters for process job call.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="290"/>
        <source>External command failed to finish.</source>
        <translation>외부 명령을 완료하지 못했습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="291"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
        <translation>&lt;i&gt;%1&lt;/i&gt; 명령을 %2초 안에 완료하지 못했습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="297"/>
        <source>External command finished with errors.</source>
        <translation>외부 명령이 오류와 함께 완료되었습니다.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="298"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
        <translation>&lt;i&gt;%1&lt;/i&gt; 명령이 종료 코드 %2와 함께 완료되었습니다.</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>기본 키보드 모델</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>기본</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="207"/>
        <source>unknown</source>
        <translation>알 수 없음</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="209"/>
        <source>extended</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="211"/>
        <source>unformatted</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="213"/>
        <source>swap</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
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
        <source>The installer failed to remove a volume group named &apos;%1&apos;.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ReplaceWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="134"/>
        <source>Select where to install %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="160"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation>선택된 항목은 유효한 파티션으로 표시되지 않습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation>%1은 빈 공간에 설치될 수 없습니다. 존재하는 파티션을 선택해주세요.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation>%1은 확장 파티션에 설치될 수 없습니다. 주 파티션 혹은 논리 파티션을 선택해주세요.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="188"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation>%1은 이 파티션에 설치될 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="194"/>
        <source>Data partition (%1)</source>
        <translation>데이터 파티션 (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="211"/>
        <source>Unknown system partition (%1)</source>
        <translation>알 수 없는 시스템 파티션 (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
        <source>%1 system partition (%2)</source>
        <translation>%1 시스템 파티션 (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="227"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="250"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="278"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="302"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="270"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>%1의 EFI 시스템 파티션은 %2의 시작으로 사용될 것입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <source>EFI system partition:</source>
        <translation>EFI 시스템 파티션:</translation>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="68"/>
        <source>Gathering system information...</source>
        <translation>시스템 정보 수집 중...</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="118"/>
        <source>has at least %1 GB available drive space</source>
        <translation>최소 %1 GB의 여유 공간이 필요합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="120"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation>저장 공간이 충분하지 않습니다. 최소 %1 GB의 공간이 필요합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="128"/>
        <source>has at least %1 GB working memory</source>
        <translation>최소 %1 GB의 가용 메모리가 필요합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="130"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation>이 시스템은 가용 메모리가 충분하지 않습니다. 최소 %1 GB의 가용 메모리가 필요합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="138"/>
        <source>is plugged in to a power source</source>
        <translation>전원 공급이 연결되어 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="139"/>
        <source>The system is not plugged in to a power source.</source>
        <translation>이 시스템은 전원 공급이 연결되어 있지 않습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="146"/>
        <source>is connected to the Internet</source>
        <translation>인터넷에 연결되어 있습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="147"/>
        <source>The system is not connected to the Internet.</source>
        <translation>이 시스템은 인터넷에 연결되어 있지 않습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="155"/>
        <source>The installer is not running with administrator rights.</source>
        <translation>설치 관리자가 관리자 권한으로 동작하고 있지 않습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="163"/>
        <source>The screen is too small to display the installer.</source>
        <translation>설치 관리자를 표시하기에 화면이 너무 작습니다.</translation>
    </message>
</context>
<context>
    <name>ResizeFSJob</name>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="130"/>
        <source>Resize Filesystem Job</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="238"/>
        <source>Invalid configuration</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="239"/>
        <source>The file-system resize job has an invalid configuration and will not run.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="253"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="263"/>
        <source>KPMCore not Available</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="254"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="264"/>
        <source>Calamares cannot start KPMCore for the file-system resize job.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="272"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="281"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="294"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="303"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="320"/>
        <source>Resize Failed</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="273"/>
        <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="274"/>
        <source>The device %1 could not be found in this system, and cannot be resized.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="282"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="295"/>
        <source>The filesystem %1 cannot be resized.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="283"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="296"/>
        <source>The device %1 cannot be resized.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="304"/>
        <source>The filesystem %1 must be resized, but cannot.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="305"/>
        <source>The device %1 must be resized, but cannot</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
        <source>Resize partition %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="55"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="66"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="85"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
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
        <source>The installer failed to resize a volume group named &apos;%1&apos;.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Scanning storage devices...</source>
        <translation>스토리지 장치 검색 중...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
        <source>Partitioning</source>
        <translation>파티셔닝</translation>
    </message>
</context>
<context>
    <name>SetHostNameJob</name>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="38"/>
        <source>Set hostname %1</source>
        <translation>호스트 이름을 %1로 설정합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="45"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>호스트 이름을 &lt;strong&gt;%1&lt;/strong&gt;로 설정합니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="52"/>
        <source>Setting hostname %1.</source>
        <translation>호스트 이름을 %1로 설정하는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="62"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="69"/>
        <source>Internal Error</source>
        <translation>내부 오류</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="76"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="87"/>
        <source>Cannot write hostname to target system</source>
        <translation>시스템의 호스트 이름을 저장할 수 없습니다</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>키보드 모델을 %1로 설정하고, 레이아웃을 %2-%3으로 설정합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="321"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>가상 콘솔을 위한 키보드 설정을 저장할 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="322"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="326"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="332"/>
        <source>Failed to write to %1</source>
        <translation>%1에 쓰기를 실패했습니다</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="325"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>X11에 대한 키보드 설정을 저장하지 못했습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="331"/>
        <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
        <translation>/etc/default 디렉터리에 키보드 설정을 저장하지 못했습니다.</translation>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
        <source>Set flags on partition %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
        <source>Set flags on %1MB %2 partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
        <source>Set flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
        <source>Clear flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
        <source>Clear flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="79"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="85"/>
        <source>Flag %1MB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
        <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="103"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="107"/>
        <source>Clearing flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="111"/>
        <source>Clearing flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="115"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="121"/>
        <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="127"/>
        <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="144"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
        <source>Set password for user %1</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
        <source>Setting password for user %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
        <source>Bad destination system path.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
        <source>rootMountPoint is %1</source>
        <translation type="unfinished"/>
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
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="141"/>
        <source>usermod terminated with error code %1.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>표준시간대를 %1/%2로 설정합니다</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>선택된 표준시간대 경로에 접근할 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>잘못된 경로: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>표준 시간대를 설정할 수 없습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>링크 생성 실패, 대상: %1; 링크 이름: %2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot set timezone,</source>
        <translation>표준시간대를 설정할 수 없습니다,</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="97"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation>/etc/timezone을 쓰기를 위해 열 수 없습니다.</translation>
    </message>
</context>
<context>
    <name>ShellProcessJob</name>
    <message>
        <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="51"/>
        <source>Shell Processes Job</source>
        <translation>셸 처리 작업</translation>
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
        <location filename="../src/modules/summary/SummaryPage.cpp" line="49"/>
        <source>This is an overview of what will happen once you start the install procedure.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>요약</translation>
    </message>
</context>
<context>
    <name>TrackingInstallJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="43"/>
        <source>Installation feedback</source>
        <translation>설치 피드백</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="53"/>
        <source>Sending installation feedback.</source>
        <translation>설치 피드백을 보내는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="88"/>
        <source>Internal error in install-tracking.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="89"/>
        <source>HTTP request timed out.</source>
        <translation>HTTP 요청 시간이 만료되었습니다.</translation>
    </message>
</context>
<context>
    <name>TrackingMachineNeonJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="104"/>
        <source>Machine feedback</source>
        <translation>장치 피드백</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="114"/>
        <source>Configuring machine feedback.</source>
        <translation>장치 피드백을 설정하는 중입니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="133"/>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="136"/>
        <source>Error in machine feedback configuration.</source>
        <translation>장치 피드백 설정 중에 오류가 발생했습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="134"/>
        <source>Could not configure machine feedback correctly, script error %1.</source>
        <translation>장치 피드백을 정확하게 설정할 수 없습니다, %1 스크립트 오류.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="137"/>
        <source>Could not configure machine feedback correctly, Calamares error %1.</source>
        <translation>장치 피드백을 정확하게 설정할 수 없습니다, %1 깔라마레스 오류.</translation>
    </message>
</context>
<context>
    <name>TrackingPage</name>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
        <source>Form</source>
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
        <source>Placeholder</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=&quot; font-weight:600;&quot;&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="123"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="185"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="247"/>
        <source>TextLabel</source>
        <translation type="unfinished"/>
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
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
        <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="45"/>
        <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="46"/>
        <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="47"/>
        <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>TrackingViewStep</name>
    <message>
        <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="59"/>
        <source>Feedback</source>
        <translation>피드백</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="289"/>
        <source>Your username is too long.</source>
        <translation>사용자 이름이 너무 깁니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="295"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation>사용자 이름이 유효하지 않은 문자들을 포함하고 있습니다. 소문자 그리고 숫자만이 허용됩니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="333"/>
        <source>Your hostname is too short.</source>
        <translation>호스트 이름이 너무 짧습니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="339"/>
        <source>Your hostname is too long.</source>
        <translation>호스트 이름이 너무 깁니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="345"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>호트스 이름이 유효하지 않은 문자들을 포함하고 있습니다. 영문자, 숫자 그리고 붙임표(-)만이 허용됩니다.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="373"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="417"/>
        <source>Your passwords do not match!</source>
        <translation>암호가 일치하지 않습니다!</translation>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="53"/>
        <source>Users</source>
        <translation>사용자</translation>
    </message>
</context>
<context>
    <name>VolumeGroupBaseDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
        <source>VolumeGroupDialog</source>
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
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
        <source>Total Size:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="92"/>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="112"/>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="132"/>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="152"/>
        <source>---</source>
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
        <translation>형식</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
        <source>&amp;Language:</source>
        <translation>언어(&amp;L):</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation>출시 정보(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation>알려진 문제(&amp;K)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation>지원(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation>정보(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;%1 설치 관리자에 오신 것을 환영합니다.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;%1을 위한 깔라마레스 설치 관리자에 오신 것을 환영합니다.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="73"/>
        <source>About %1 installer</source>
        <translation>%1 설치 관리자에 대하여</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="75"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;https://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="290"/>
        <source>%1 support</source>
        <translation>%1 지원</translation>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="52"/>
        <source>Welcome</source>
        <translation>환영합니다</translation>
    </message>
</context>
</TS>
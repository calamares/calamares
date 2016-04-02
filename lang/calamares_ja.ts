<?xml version="1.0" ?><!DOCTYPE TS><TS language="ja" version="2.1">
<context>
    <name>AlongsidePage</name>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="77"/>
        <source>Choose partition to shrink:</source>
        <translation>縮小するパーティションを選択してください:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="78"/>
        <source>Allocate drive space by dragging the divider below:</source>
        <translation>下の仕切りをドラッグして、ドライブの空き容量を割り当ててください:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="121"/>
        <source>With this operation, the partition &lt;strong&gt;%1&lt;/strong&gt; which contains %4 will be shrunk to %2MB and a new %3MB partition will be created for %5.</source>
        <translation>この操作によって、%4 を含むパーティション &lt;strong&gt;%1&lt;/strong&gt;が %2MB に縮小し、%5 のための新しい %3MBのパーティションが作成されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="198"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>システムにEFIシステムパーティションが存在しません。%1 のセットアップのため、元に戻り、手動パーティショニングを使用してください。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="208"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>%1 上の EFI システムパーテイションは %2 の開始時に使用します。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="218"/>
        <source>EFI system partition:</source>
        <translation>EFI システムパーティション:</translation>
    </message>
</context>
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="61"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation>このシステムの &lt;strong&gt;ブート環境。&lt;/strong&gt;&lt;br&gt;&lt;br&gt;古いx86システムは&lt;strong&gt;BIOS&lt;/strong&gt;のみサポートしています。&lt;br&gt;最近のシステムは通常&lt;strong&gt;EFI&lt;/strong&gt;を使用しますが、互換モードが起動できる場合はBIOSが現れる場合もあります。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="75"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation>このシステムは&lt;strong&gt;EFI&lt;/strong&gt; ブート環境で起動しました。&lt;br&gt;&lt;br&gt;EFI環境からの起動について設定するためには、&lt;strong&gt;EFI システムパーティション&lt;/strong&gt;に &lt;strong&gt;GRUB&lt;/strong&gt; あるいは &lt;strong&gt;systemd-boot&lt;/strong&gt; といったブートローダーアプリケーションを配置しなければなりません。手動によるパーティショニングを選択する場合、EFI システムパーティションを選択あるいは作成しなければなりません。そうでない場合は、この操作は自動的に行われます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="87"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation>このシステムは &lt;strong&gt;BIOS&lt;/strong&gt; ブート環境で起動しました。&lt;br&gt;&lt;br&gt; BIOS環境からの起動について設定するためには、パーティションの開始位置あるいはパーティションテーブルの開始位置の近く(推奨)にある&lt;strong&gt;マスターブートレコード&lt;/strong&gt;に &lt;strong&gt;GRUB&lt;/strong&gt; のようなブートローダーをインストールしなければなりません。手動によるパーティショニングを選択する場合はユーザー自身で設定しなければなりません。そうでない場合は、この操作は自動的に行われます。</translation>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation>%1 のマスターブートレコード</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>ブートパーティション</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>システムパーティション</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation>ブートローダーをインストールしない</translation>
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
        <translation>Form</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="24"/>
        <source>GlobalStorage</source>
        <translation>グローバルストレージ</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation>ジョブキュー</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation>モジュール</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Tools</source>
        <translation>ツール</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="102"/>
        <source>Debug information</source>
        <translation>デバッグ情報</translation>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="77"/>
        <source>Install</source>
        <translation>インストール</translation>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="89"/>
        <source>Done</source>
        <translation>完了</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="51"/>
        <source>Run command %1 %2</source>
        <translation>コマンド %1 %2 を実行</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="60"/>
        <source>Running command %1 %2</source>
        <translation>コマンド %1 %2 を実行中</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="89"/>
        <source>External command crashed</source>
        <translation>外部コマンドがクラッシュしました</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="90"/>
        <source>Command %1 crashed.
Output:
%2</source>
        <translation>コマンド %1 がクラッシュ
出力:
%2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="95"/>
        <source>External command failed to start</source>
        <translation>外部コマンドの開始に失敗</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="96"/>
        <source>Command %1 failed to start.</source>
        <translation>コマンド %1 の開始に失敗</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="100"/>
        <source>Internal error when starting command</source>
        <translation>コマンド開始時における内部エラー</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="101"/>
        <source>Bad parameters for process job call.</source>
        <translation>ジョブ呼び出しにおける不正なパラメータ</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="104"/>
        <source>External command failed to finish</source>
        <translation>外部コマンドの完了に失敗</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="105"/>
        <source>Command %1 failed to finish in %2s.
Output:
%3</source>
        <translation>%2s においてコマンド %1 が完了に失敗しました。
出力:
%3 </translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="111"/>
        <source>External command finished with errors</source>
        <translation>外部コマンドでエラー</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="112"/>
        <source>Command %1 finished with exit code %2.
Output:
%3</source>
        <translation>コマンド %1 がコード %2 によって終了しました
出力:
%3</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="241"/>
        <source>Running %1 operation.</source>
        <translation>%1 操作を実行中。</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="254"/>
        <source>Bad working directory path</source>
        <translation>作業ディレクトリパスが不正です</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="255"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>python ジョブ %2 において作業ディレクトリ %1 が読み込めません。</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="265"/>
        <source>Bad main script file</source>
        <translation>不正なメインスクリプトファイル</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="266"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>python ジョブ %2 におけるメインスクリプトファイル %1 が読み込めません。</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="311"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>ジョブ &quot;%1&quot; での Boost.Python エラー。</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="65"/>
        <source>&amp;Back</source>
        <translation>戻る (&amp;B)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="66"/>
        <source>&amp;Next</source>
        <translation>次へ (&amp;N)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="67"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="295"/>
        <source>&amp;Cancel</source>
        <translation>中止 (&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="90"/>
        <source>Cancel installation?</source>
        <translation>インストールを中止しますか？</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="91"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>本当に現在の作業を中止しますか？
すべての変更が取り消されます。</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="224"/>
        <source>Continue with setup?</source>
        <translation>セットアップを続行しますか？</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="225"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation>%1 インストーラーは %2 をインストールするためにディスクの内容を変更しようとします。&lt;br/&gt;&lt;strong&gt;これらの変更は取り消しできなくなります。&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="232"/>
        <source>&amp;Install now</source>
        <translation>今すぐインストール (&amp;I)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="233"/>
        <source>Go &amp;back</source>
        <translation>戻る (&amp;B)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="264"/>
        <source>&amp;Quit</source>
        <translation>終了 (&amp;Q)</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="170"/>
        <source>Error</source>
        <translation>エラー</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="171"/>
        <source>Installation Failed</source>
        <translation>インストールに失敗</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="234"/>
        <source>Unknown exception type</source>
        <translation>不明な例外タイプ</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="247"/>
        <source>unparseable Python error</source>
        <translation>解析不能な Python エラー</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="263"/>
        <source>unparseable Python traceback</source>
        <translation>解析不能な Python トレースバック</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="267"/>
        <source>Unfetchable Python error.</source>
        <translation>取得不能な Python エラー。</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="44"/>
        <source>%1 Installer</source>
        <translation>%1 インストーラー</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="98"/>
        <source>Show debug information</source>
        <translation>デバッグ情報を表示</translation>
    </message>
</context>
<context>
    <name>CheckFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="34"/>
        <source>Checking file system on partition %1.</source>
        <translation>パーティション %1 のファイルシステムをチェック中。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="58"/>
        <source>The file system check on partition %1 failed.</source>
        <translation>%1 ファイルシステムのチェックに失敗しました。</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="95"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation>このコンピュータは %1 をインストールするための最低要件を満たしていません。&lt;br/&gt;インストールは続行できません。&lt;a href=&quot;#details&quot;&gt;詳細...&lt;/a&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation>このコンピュータは %1 をインストールするための推奨条件をいくつか満たしていません。&lt;br/&gt;インストールは続行しますが、一部の機能が無効になる場合があります。</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="142"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation>このプログラムはあなたにいくつか質問をして、コンピュータ上で %2 を設定します。</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="166"/>
        <source>For best results, please ensure that this computer:</source>
        <translation>良好な結果を得るために、このコンピュータについて以下の項目を確認してください:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="194"/>
        <source>System requirements</source>
        <translation>システム要件</translation>
    </message>
</context>
<context>
    <name>ChoicePage</name>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="117"/>
        <source>After:</source>
        <translation>後:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="223"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation>&lt;strong&gt;手動パーティション&lt;/strong&gt;&lt;br/&gt;パーティションの作成、あるいはサイズ変更を行うことができます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="808"/>
        <source>Boot loader location:</source>
        <translation>ブートローダーの場所:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="755"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation>%1 は %2 MB に縮小され、新しい %3 MB のパーティションが %4 のために作成されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="115"/>
        <source>Select storage de&amp;vice:</source>
        <translation>ストレージデバイスを選択(&amp;V):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="116"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="740"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="779"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="855"/>
        <source>Current:</source>
        <translation>現在:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="741"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;縮小するパーティションを選択し、その下にあるバーをドラッグしてサイズを変更して下さい&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="846"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;インストールするパーティションの選択&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="901"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>システムにEFIシステムパーティションが存在しません。%1 のセットアップのため、元に戻り、手動パーティショニングを使用してください。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="911"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>%1 上のEFIシステムパーテイションは %2 のスタートに使用されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="920"/>
        <source>EFI system partition:</source>
        <translation>EFI システムパーティション:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1005"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>このストレージデバイスは、オペレーティングシステムを持っていないようです。どうしますか？&lt;br/&gt;ストレージデバイスに対する変更が実施される前に、変更点をレビューし、確認することができます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1010"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1050"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1074"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1112"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation>&lt;strong&gt;ディスクの消去&lt;/strong&gt;&lt;br/&gt;選択したストレージデバイス上のデータがすべて &lt;font color=&quot;red&quot;&gt;削除&lt;/font&gt; されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1039"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>このストレージデバイスは %1 を有しています。どうしますか?&lt;br/&gt;ストレージデバイスに対する変更が実施される前に、変更点をレビューし、確認することができます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1014"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1045"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1069"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1107"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation>&lt;strong&gt;共存してインストール&lt;/strong&gt;&lt;br/&gt;インストーラは %1 用の空きスペースを確保するため、パーティションを縮小します。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1019"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1055"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1078"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1116"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation>&lt;strong&gt;パーティションの置換&lt;/strong&gt;&lt;br/&gt;パーティション %1 に置き換えます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1064"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>この記憶装置は、すでにオペレーティングシステムが存在します。どうしますか?&lt;br/&gt;ストレージデバイスに対する変更が実施される前に、変更点をレビューし、確認することができます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1102"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>このストレージデバイスには、複数のオペレーティングシステムが存在します。どうしますか？&lt;br /&gt;ストレージデバイスに対する変更が実施される前に、変更点をレビューし、確認することができます。</translation>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="44"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation>%1 のパーティション操作のため、マウントを解除</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="52"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation>%1 のパーティション操作のため、マウントを解除中</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="171"/>
        <source>Cleared all mounts for %1</source>
        <translation>%1 のすべてのマウントを解除</translation>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="40"/>
        <source>Clear all temporary mounts.</source>
        <translation>すべての一時的なマウントをクリア</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="47"/>
        <source>Clearing all temporary mounts.</source>
        <translation>すべての一時的なマウントをクリアしています。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="58"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation>一時的なマウントのリストを取得できません。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="97"/>
        <source>Cleared all temporary mounts.</source>
        <translation>すべての一時的なマウントを解除しました。</translation>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>パーティションの生成</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Partition &amp;Type:</source>
        <translation>パーティションの種類 (&amp;T) :</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="50"/>
        <source>&amp;Primary</source>
        <translation>プライマリ (&amp;P)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="60"/>
        <source>E&amp;xtended</source>
        <translation>拡張 (&amp;X)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="89"/>
        <source>Fi&amp;le System:</source>
        <translation>ファイルシステム （&amp;L）:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="181"/>
        <source>Flags:</source>
        <translation>フラグ:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="118"/>
        <source>&amp;Mount Point:</source>
        <translation>マウントポイント (&amp;M)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="164"/>
        <source>Si&amp;ze:</source>
        <translation>サイズ (&amp;Z)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="174"/>
        <source> MB</source>
        <translation> MB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="136"/>
        <source>Logical</source>
        <translation>論理</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="141"/>
        <source>Primary</source>
        <translation>プライマリ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="158"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="48"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation>ファイルシステム %1 で %4 (%3) 上に新しく %2MB のパーティションを作成</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="59"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>ファイルシステム %1で &lt;strong&gt;%4&lt;/strong&gt; (%3) 上に新しく&lt;strong&gt;%2MB&lt;/strong&gt;のパーティションを作成</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="71"/>
        <source>Creating new %1 partition on %2.</source>
        <translation>%2 上に新しく %1 パーティションを作成中</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="83"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation>インストーラーはディスク &apos;%1&apos; にパーティションを作成することに失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="92"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>デバイス &apos;%1&apos; を開けませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="102"/>
        <source>Could not open partition table.</source>
        <translation>パーティションテーブルを開くことができませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="126"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>インストーラーは %1 パーティション上でのファイルシステムの作成に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="134"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>インストーラーはディスク &apos;%1&apos; 上にあるパーティションテーブルの更新に失敗しました。</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>パーティションテーブルの作成</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>パーティションテーブルを作成することによって、ディスク上のデータがすべて削除されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>どの種類のパーティションテーブルを作成しますか?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
        <source>Master Boot Record (MBR)</source>
        <translation>マスターブートレコード (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
        <source>GUID Partition Table (GPT)</source>
        <translation>GUID パーティションテーブル (GPT)</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="49"/>
        <source>Create new %1 partition table on %2.</source>
        <translation>%2 上に新しく %1 パーティションテーブルを作成</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="56"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt; (%3) 上に新しく &lt;strong&gt;%1&lt;/strong&gt; パーティションテーブルを作成</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="66"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation>%2 上に新しく %1 パーティションテーブルを作成中</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="76"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>インストーラーは%1 上でのパーティションテーブルの作成に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="84"/>
        <source>Could not open device %1.</source>
        <translation>デバイス %1 を開けませんでした。</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="49"/>
        <source>Create user %1</source>
        <translation>ユーザー %1 を作成</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="56"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>ユーザー  &lt;strong&gt;%1&lt;/strong&gt; を作成。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="63"/>
        <source>Creating user %1.</source>
        <translation>ユーザー %1 を作成中。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="79"/>
        <source>Sudoers dir is not writable.</source>
        <translation>sudoers ディレクトリに書き込みできません。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="83"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>sudoers ファイルを作成できません。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="91"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>sudoers のファイル権限を変更できません。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="97"/>
        <source>Cannot open groups file for reading.</source>
        <translation>groups ファイルを読み込めません。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="136"/>
        <source>Cannot create user %1.</source>
        <translation>ユーザー %1 を作成できません。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="138"/>
        <source>useradd terminated with error code %1.</source>
        <translation>エラーコード %1 により useradd を中止しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="143"/>
        <source>Cannot set full name for user %1.</source>
        <translation>ユーサー %1 のフルネームを設定できません。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="145"/>
        <source>chfn terminated with error code %1.</source>
        <translation>エラーコード %1 により chfn は中止しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="155"/>
        <source>Cannot set home directory ownership for user %1.</source>
        <translation>ユーザー %1 のホームディレクトリの所有者を設定できません。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="157"/>
        <source>chown terminated with error code %1.</source>
        <translation>エラーコード %1 により chown は中止しました。</translation>
    </message>
</context>
<context>
    <name>DeletePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="42"/>
        <source>Delete partition %1.</source>
        <translation>パーティション %1 の削除</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="50"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>パーティション  &lt;strong&gt;%1&lt;/strong&gt; の削除</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="58"/>
        <source>Deleting partition %1.</source>
        <translation>パーティション %1 の削除中。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="67"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>インストーラーはパーティション %1 の削除に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="73"/>
        <source>Partition (%1) and device (%2) do not match.</source>
        <translation>パーティション (%1) とデバイス (%2) が適合しません。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="85"/>
        <source>Could not open device %1.</source>
        <translation>デバイス %1 を開けませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="94"/>
        <source>Could not open partition table.</source>
        <translation>パーティションテーブルを開くことができませんでした。</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="63"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation>選択したストレージデバイスにおける&lt;strong&gt; パーティションテーブル &lt;/strong&gt; の種類。 &lt;br&gt;&lt;br&gt; パーティションテーブルの種類を変更する唯一の方法は、パーティションテーブルを消去し、最初から再作成を行うことですが、この操作はストレージ上の全てのデータを破壊します。 &lt;br&gt; このインストーラーは、他の種類へ明示的に変更ししない限り、現在のパーティションテーブルが保持されます。よくわからない場合、最近のシステムではGPTが推奨されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation>このデバイスのパーティションテーブルは &lt;strong&gt;%1&lt;/strong&gt; です。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation>このデバイスは&lt;strong&gt;ループ&lt;/strong&gt; デバイスです。&lt;br&gt;&lt;br&gt; ブロックデバイスとしてふるまうファイルを作成する、パーティションテーブルを持たない仮想デバイスです。このセットアップの種類は通常単一のファイルシステムで構成されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation>インストーラが、選択したストレージデバイス上の&lt;strong&gt;パーティションテーブルを検出することができません。&lt;/strong&gt;&lt;br&gt;&lt;br&gt;デバイスにはパーティションテーブルが存在しないか、パーティションテーブルが未知のタイプまたは破損しています。&lt;br&gt;このインストーラーでは、自動であるいは、パーティションページによって手動で、新しいパーティションテーブルを作成することができます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation>&lt;br&gt;&lt;br&gt;これは &lt;strong&gt;EFI&lt;/ strong&gt; ブート環境から起動する現在のシステムで推奨されるパーティションテーブルの種類です。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="137"/>
        <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
        <translation>&lt;br&gt;&lt;br&gt;このパーティションテーブルの種類は&lt;strong&gt;BIOS&lt;/strong&gt; ブート環境から起動する古いシステムにおいてのみ望ましいものです。他の多くの場合ではGPTが推奨されます。&lt;br&gt;&lt;br&gt;&lt;strong&gt;警告:&lt;/strong&gt; MBR パーティションテーブルは時代遅れのMS-DOS時代の標準です。&lt;br&gt;わずか 4 つだけの&lt;em&gt;プライマリ&lt;/em&gt;パーティションが作成され、そのうち1つについては、多くの&lt;em&gt;論理&lt;/em&gt;パーティションを含む&lt;em&gt;拡張&lt;/em&gt;パーティションにすることができます。</translation>
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
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>既存のパーティションの編集</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>内容:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation>保持 (&amp;K)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>フォーマット</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>警告: パーティションのフォーマットはすべてのデータを削除します。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>マウントポイント (&amp;M)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation>サイズ (&amp;Z):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="132"/>
        <source>Fi&amp;le System:</source>
        <translation>ファイルシステム (&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="145"/>
        <source>Flags:</source>
        <translation>フラグ:</translation>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="88"/>
        <source>Set partition information</source>
        <translation>パーティション情報の設定</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="111"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation>&lt;strong&gt;新しい&lt;/strong&gt; %2 システムパーティションに %1 をインストール。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="116"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>マウントポイント &lt;strong&gt;%1&lt;/strong&gt; に &lt;strong&gt;新しい&lt;/strong&gt; %2 パーティションをセットアップ。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="124"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>%3 システムパーティション &lt;strong&gt;%1&lt;/strong&gt; に %2 をインストール。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="130"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>パーティション &lt;strong&gt;%1&lt;/strong&gt;  マウントポイント &lt;strong&gt;%2&lt;/strong&gt;  に %3 をセットアップ。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="142"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt; にブートローダーをインストール</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="152"/>
        <source>Setting up mount points.</source>
        <translation>マウントポイントの設定。</translation>
    </message>
</context>
<context>
    <name>FinishedPage</name>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="77"/>
        <source>&amp;Restart now</source>
        <translation>今すぐ再起動 (&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="50"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation>&lt;h1&gt;すべて完了しました。&lt;/h1&gt;&lt;br/&gt;%1 はコンピュータにインストールされました。&lt;br/&gt;再起動して新しいシステムを立ち上げるか、%2 Live環境を使用し続けることができます。</translation>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="43"/>
        <source>Finish</source>
        <translation>終了</translation>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="48"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation>%4 上でパーティション %1 (ファイルシステム: %2, サイズ: %3 MB) のフォーマット</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="59"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;%3MB&lt;/strong&gt; パーティション &lt;strong&gt;%1&lt;/strong&gt; をファイルシステム &lt;strong&gt;%2&lt;/strong&gt;でフォーマット。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="70"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation>ファイルシステム %2 でパーティション %1 をフォーマット中。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="82"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>インストーラーはディスク &apos;%2&apos; 上のパーティション %1 のフォーマットに失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="90"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>デバイス &apos;%1&apos; を開けませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="99"/>
        <source>Could not open partition table.</source>
        <translation>パーティションテーブルを開くことができませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="107"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>インストーラーは %1 パーティションのシステム作成に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="115"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>インストーラーはディスク &apos;%1&apos; 上にあるパーティションテーブルの更新に失敗しました。</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="69"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="84"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="96"/>
        <source>Konsole not installed</source>
        <translation>konsole がインストールされていません</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="70"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="85"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="97"/>
        <source>Please install the kde konsole and try again!</source>
        <translation>kde konsoleをインストールして、再度行ってください！</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="122"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation>スクリプトの実行: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation>スクリプト</translation>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="201"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>キーボードのモデルを %1 に設定。&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="203"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>キーボードのレイアウトを %1/%2 に設定。</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="49"/>
        <source>Keyboard</source>
        <translation>キーボード</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="33"/>
        <source>System locale setting</source>
        <translation>システムロケールの設定</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="40"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>システムロケールの設定はコマンドラインやインターフェース上での言語や文字の表示に影響をおよぼします。&lt;br/&gt;現在の設定 &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
</context>
<context>
    <name>LicensePage</name>
    <message>
        <location filename="../src/modules/license/LicensePage.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="88"/>
        <source>I accept the terms and conditions above.</source>
        <translation>上記の項目及び条件に同意します。</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="115"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation>&lt;h1&gt;ライセンス契約条項&lt;/h1&gt; このセットアップはライセンス条項に従うことが必要なプロプライエタリなソフトウェアをインストールします。</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="118"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation>上記のエンドユーザーライセンス条項 (EULAs) を確認してください。&lt;br/&gt;もしライセンス条項に同意できない場合、セットアップを続行することはできません。</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="124"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation>&lt;h1&gt;ライセンス契約条項&lt;/h1&gt; このセットアップは、機能を追加し、ユーザーの使いやすさを向上させるために、ライセンス条項に従うことが必要なプロプライエタリなソフトウェアをインストールします。</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="129"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation>上記のエンドユーザーライセンス条項 (EULAs) を確認してください。&lt;br/&gt;もしライセンス条項に同意できない場合、プロプライエタリなソフトウェアはインストールされず、代わりにオープンソースのソフトウェアが使用されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation>&lt;strong&gt;%1 ドライバー&lt;/strong&gt;&lt;br/&gt;by %2</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="166"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation>&lt;strong&gt;%1 グラフィックドライバー&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="172"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 ブラウザプラグイン&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="178"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="184"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 パッケージ&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="190"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="202"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation>&lt;a href=&quot;%1&quot;&gt;ライセンスへの同意&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation>ライセンス</translation>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="158"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="169"/>
        <source>The system locale is set to %1.</source>
        <translation>システムロケールが %1 に設定されました。</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="166"/>
        <source>Region:</source>
        <translation>地域:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="167"/>
        <source>Zone:</source>
        <translation>ゾーン:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="172"/>
        <source>&amp;Change...</source>
        <translation>変更 (&amp;C)...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="271"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>タイムゾーンを  %1/%2 に設定。&lt;br/&gt;</translation>
    </message>
</context>
<context>
    <name>LocaleViewStep</name>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="48"/>
        <source>Loading location data...</source>
        <translation>ロケーションデータをロード中...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="82"/>
        <source>Location</source>
        <translation>ロケーション</translation>
    </message>
</context>
<context>
    <name>MoveFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="66"/>
        <source>Move file system of partition %1.</source>
        <translation>パーティション %1 のファイルシステムを移動</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="80"/>
        <source>Could not open file system on partition %1 for moving.</source>
        <translation>パーティション %1 のファイルシステムを開けませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="86"/>
        <source>Could not create target for moving file system on partition %1.</source>
        <translation>パーティション %1 上のファイルシステムを移動させるためのターゲットを作成できませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="95"/>
        <source>Moving of partition %1 failed, changes have been rolled back.</source>
        <translation>パーティション %1 の移動に失敗しました。変更内容は戻されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="101"/>
        <source>Moving of partition %1 failed. Roll back of the changes have failed.</source>
        <translation>パーティション %1 の移動に失敗しました。変更からのロールバックに失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="113"/>
        <source>Updating boot sector after the moving of partition %1 failed.</source>
        <translation>パーティション %1 の移動後のブートセクターの更新に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="127"/>
        <source>The logical sector sizes in the source and target for copying are not the same. This is currently unsupported.</source>
        <translation>ソースとターゲットの論理セクタサイズが異なります。これは現在サポートされていません。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="197"/>
        <source>Source and target for copying do not overlap: Rollback is not required.</source>
        <translation>コピーのためのソースとターゲットは領域が重なりません。ロールバックを行う必要はありません。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="221"/>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="229"/>
        <source>Could not open device %1 to rollback copying.</source>
        <translation>ロールバック用のデバイス %1 を開く事ができませんでした。</translation>
    </message>
</context>
<context>
    <name>Page_Keyboard</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
        <source>Keyboard Model:</source>
        <translation>キーボードモデル:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>ここでタイプしてキーボードをテストしてください</translation>
    </message>
</context>
<context>
    <name>Page_UserSetup</name>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
        <source>What is your name?</source>
        <translation>名前は何ですか?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>ログインではどの名前を使用しますか?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="197"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation>font-weight: normal</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;複数人がこのコンピュータを使用する場合、インストール後に複数のアカウントを設定することができます。&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>アカウントを安全に使うため、パスワードを選択してください</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation>&lt;small&gt;入力ミスを確認することができるよう、同じパスワードを 2 回入力します。良いパスワードにするためには 8文字以上にする必要があり、英文・数字・句読点を組み合わせたものにします。パスワードは定期的に変更してください。&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>このコンピュータの名前は何ですか？</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation>&lt;small&gt;ネットワーク上から他の人よりコンピュータが見えるようにする場合、この名前が使用されます。&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation>パスワードの入力を求めず自動的にログインする</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation>管理者アカウントに同じパスワードを使用する</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>管理者アカウントのパスワードを選択する</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;入力ミスを確認することができるように、同じパスワードを 2 回入力します。&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="191"/>
        <source>Root</source>
        <translation>Root</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="194"/>
        <source>Home</source>
        <translation>Home</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Boot</source>
        <translation>Boot</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="199"/>
        <source>EFI system</source>
        <translation>EFI システム</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>Swap</source>
        <translation>スワップ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>New partition for %1</source>
        <translation>新しいパーティション %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="220"/>
        <source>%1  %2</source>
        <translation>%1  %2</translation>
    </message>
</context>
<context>
    <name>PartitionModel</name>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="137"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="169"/>
        <source>Free Space</source>
        <translation>空き領域</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="141"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="173"/>
        <source>New partition</source>
        <translation>新しいパーティション</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="242"/>
        <source>Name</source>
        <translation>名前</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="244"/>
        <source>File System</source>
        <translation>ファイルシステム</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="246"/>
        <source>Mount Point</source>
        <translation>マウントポイント</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="248"/>
        <source>Size</source>
        <translation>サイズ</translation>
    </message>
</context>
<context>
    <name>PartitionPage</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
        <source>Storage de&amp;vice:</source>
        <translation>
ストレージデバイス (&amp;V):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>すべての変更を元に戻す (&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="84"/>
        <source>New Partition &amp;Table</source>
        <translation>新しいパーティションテーブル (&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="104"/>
        <source>&amp;Create</source>
        <translation>作成 (&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
        <source>&amp;Edit</source>
        <translation>編集 (&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
        <source>&amp;Delete</source>
        <translation>削除 (&amp;D)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="145"/>
        <source>Install boot &amp;loader on:</source>
        <translation>ブートローダーインストール先 (&amp;L):</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="147"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation>％1 上で新しいパーティションテーブルを作成します。よろしいですか？</translation>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="67"/>
        <source>Gathering system information...</source>
        <translation>システム情報を取得中...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="106"/>
        <source>Partitions</source>
        <translation>パーティション</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="143"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation>他のオペレーティングシステムに&lt;strong&gt;共存して&lt;/strong&gt; %1 をインストール。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="148"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation>ディスクを&lt;strong&gt;消去&lt;/strong&gt;し %1 をインストール。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="153"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation>パーティションを %1 に&lt;strong&gt;置き換える。&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="158"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation>&lt;strong&gt;手動&lt;/strong&gt;でパーティションを設定する。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="171"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>ディスク &lt;strong&gt;%2&lt;/strong&gt; (%3) 上ののオペレーティングシステムと&lt;strong&gt;共存&lt;/strong&gt;して %1 をインストール。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="178"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation> ディスク &lt;strong&gt;%2&lt;/strong&gt; (%3) を&lt;strong&gt;消去して&lt;/strong&gt; %1 をインストール。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="185"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation>ディスク &lt;strong&gt;%2&lt;/strong&gt; (%3) 上のパーティションを %1 に&lt;strong&gt;置き換える。&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="192"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation>ディスク &lt;strong&gt;%1&lt;/strong&gt; (%2) 上で &lt;strong&gt;手動で&lt;/strong&gt;パーティショニングする。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="200"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation>ディスク &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="228"/>
        <source>Current:</source>
        <translation>現在:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="244"/>
        <source>After:</source>
        <translation>変更後:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="386"/>
        <source>No EFI system partition configured</source>
        <translation>EFI システムパーティションが設定されていません</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="387"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation>%1 を起動するためにはEFI システムパ ーティションが必要です。&lt;br/&gt;&lt;br/&gt; EFI システムパーティションを設定するためには、元に戻って、マウントポイント&lt;strong&gt;%2&lt;/strong&gt;で&lt;strong&gt;esp&lt;/strong&gt;フラグを設定したFAT32ファイルシステムを選択するか作成します。&lt;br/&gt;&lt;br/&gt;EFI システムパ ーティションの設定をせずに続行することはできますが、その場合はシステムの起動に失敗することになるかもしれません。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="401"/>
        <source>EFI system partition flag not set</source>
        <translation>EFI システムパーティションのフラグが設定されていません</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="402"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation>%1 を起動するためにはEFI システムパ ーティションが必要です。&lt;br/&gt;&lt;br/&gt;パーティションはマウントポイント&lt;strong&gt;%2&lt;/strong&gt;に設定されていますが、&lt;strong&gt;esp&lt;/strong&gt; フラグが設定されていません。&lt;br/&gt;フラグを設定するには、元に戻ってパーティションを編集してください。&lt;br/&gt;&lt;br/&gt;フラグの設定をせずに続けることはできますが、その場合、システムの起動に失敗することになるかもしれません。</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>デフォルトのキーボードモデル</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>デフォルト</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="160"/>
        <source>unknown</source>
        <translation>不明</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="162"/>
        <source>extended</source>
        <translation>拡張</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="164"/>
        <source>unformatted</source>
        <translation>未フォーマット</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
        <translation>パーティションされていない領域または未知のパーティションテーブル</translation>
    </message>
</context>
<context>
    <name>ReplaceWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="134"/>
        <source>Select where to install %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
        <translation>%1 をインストールする場所を選択します。&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;警告: &lt;/font&gt;選択したパーティション内のすべてのファイルが削除されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="161"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation>選択した項目は有効なパーティションではありません。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="169"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation>%1 は空きスペースにインストールすることはできません。既存のパーティションを選択してください。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="180"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation>%1 は拡張パーティションにインストールする事はできません。既存のプライマリまたは論理パーティションを選択してください。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="191"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation>このパーティションには %1 をインストールできません。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="198"/>
        <source>Data partition (%1)</source>
        <translation>データパーティション (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="215"/>
        <source>Unknown system partition (%1)</source>
        <translation>不明なシステムパーティション (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="220"/>
        <source>%1 system partition (%2)</source>
        <translation>%1 システムパーティション (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="231"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;パーティション %1 は、%2 には小さすぎます。少なくとも %3 GB 以上のパーティションを選択してください。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="255"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;EFI システムパーティションがシステムに見つかりません。%1 を設定するために一旦戻って手動パーティショニングを使用してください。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="267"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="311"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 は %2 にインストールされます。&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;警告: &lt;/font&gt;パーティション %2 のすべてのデータは失われます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="277"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>%1 上の EFI システムパーティションは %2 開始時に使用されます。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="295"/>
        <source>EFI system partition:</source>
        <translation>EFI システムパーティション:</translation>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="57"/>
        <source>Gathering system information...</source>
        <translation>システム情報を取得中...</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="98"/>
        <source>has at least %1 GB available drive space</source>
        <translation>最低 %1 GB のディスク空き容量があること</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="100"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation>十分なドライブ空き容量がありません。少なくとも %1 GB 必要です。</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="108"/>
        <source>has at least %1 GB working memory</source>
        <translation>最低 %1 GB のワーキングメモリーがあること</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="110"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation>システムには十分なワーキングメモリがありません。少なくとも %1 GB 必要です。</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="118"/>
        <source>is plugged in to a power source</source>
        <translation>電源が接続されていること</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="119"/>
        <source>The system is not plugged in to a power source.</source>
        <translation>システムに電源が接続されていません。</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="126"/>
        <source>is connected to the Internet</source>
        <translation>インターネットに接続されていること</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="127"/>
        <source>The system is not connected to the Internet.</source>
        <translation>システムはインターネットに接続されていません。</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="135"/>
        <source>The installer is not running with administrator rights.</source>
        <translation>インストーラーは管理者権限で実行されていません。</translation>
    </message>
</context>
<context>
    <name>ResizeFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="76"/>
        <source>Resize file system on partition %1.</source>
        <translation>パーティション %1 ファイルシステムのサイズ変更</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="91"/>
        <source>Parted failed to resize filesystem.</source>
        <translation>Parted はファイルシステムのサイズ変更に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="101"/>
        <source>Failed to resize filesystem.</source>
        <translation>ファイルシステムのサイズ変更に失敗しました。</translation>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="187"/>
        <source>Resize partition %1.</source>
        <translation>パーティション %1 のサイズを変更する。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="194"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation> &lt;strong&gt;%2MB&lt;/strong&gt; のパーティション &lt;strong&gt;%1&lt;/strong&gt; を&lt;strong&gt;%3MB&lt;/strong&gt; にサイズを変更。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="205"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation> %2MB のパーティション %1 を %3MB にサイズ変更中。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="232"/>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="298"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
        <translation>インストーラはディスク &apos;%2&apos; パーティション %1 のサイズ変更に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="237"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>デバイス &apos;%1&apos; を開けませんでした。</translation>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="83"/>
        <source>Scanning storage devices...</source>
        <translation>ストレージデバイスのスキャン中...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Partitioning</source>
        <translation>パーティショニング中</translation>
    </message>
</context>
<context>
    <name>SetHostNameJob</name>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="37"/>
        <source>Set hostname %1</source>
        <translation>ホスト名 %1 の設定</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="44"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>ホスト名 &lt;strong&gt;%1&lt;/strong&gt; の設定。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
        <source>Setting hostname %1.</source>
        <translation>ホスト名 %1 の設定中。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="61"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="68"/>
        <source>Internal Error</source>
        <translation>内部エラー</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="75"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="86"/>
        <source>Cannot write hostname to target system</source>
        <translation>ターゲットシステムにホスト名を書き込めません</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="57"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>キーボードのモデルを %1 に、レイアウトを %2-%3に設定</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="284"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>仮想コンソールでのキーボード設定の書き込みに失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="285"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="289"/>
        <source>Failed to write to %1</source>
        <translation>%1 への書き込みに失敗しました</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="288"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>X11 のためのキーボード設定の書き込みに失敗しました。</translation>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="47"/>
        <source>Set flags on partition %1.</source>
        <translation>パーティション %1 にフラグを設定。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>パーティション &lt;strong&gt;%1&lt;/strong&gt; 上のフラグを消去。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="59"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>パーティション &lt;strong&gt;%1&lt;/strong&gt; を&lt;strong&gt;%2&lt;/strong&gt;のフラグとして設定。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>パーティション &lt;strong&gt;%1&lt;/strong&gt; 上のフラグを消去中。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="74"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>パーティション &lt;strong&gt;%1&lt;/strong&gt; 上に フラグ&lt;strong&gt;%2&lt;/strong&gt;を設定。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="90"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation>インストーラーはパーティション %1 上のフラグの設定に失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="98"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>デバイス &apos;%1&apos; を開けませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="107"/>
        <source>Could not open partition table on device &apos;%1&apos;.</source>
        <translation>デバイス &apos;%1&apos; 上のパーティションテーブルを開けませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="119"/>
        <source>Could not find partition &apos;%1&apos;.</source>
        <translation>パーティション &apos;%1&apos; が見つかりませんでした。</translation>
    </message>
</context>
<context>
    <name>SetPartGeometryJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="144"/>
        <source>Update geometry of partition %1.</source>
        <translation>パーティション %1 のジオメトリーの更新</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="156"/>
        <source>Failed to change the geometry of the partition.</source>
        <translation>パーティションのジオメトリーの変更に失敗しました。</translation>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="42"/>
        <source>Set password for user %1</source>
        <translation>ユーザ %1 のパスワード設定</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="49"/>
        <source>Setting password for user %1.</source>
        <translation>ユーザ %1 のパスワード設定中。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="59"/>
        <source>Bad destination system path.</source>
        <translation>不正なシステムパス。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="60"/>
        <source>rootMountPoint is %1</source>
        <translation>root のマウントポイントは %1 。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="74"/>
        <source>Cannot set password for user %1.</source>
        <translation>ユーザ %1 のパスワードは設定できませんでした。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="76"/>
        <source>usermod terminated with error code %1.</source>
        <translation>エラーコード %1 によりusermodが停止しました。</translation>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>タイムゾーンを %1/%2 に設定</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>選択したタイムゾーンのパスにアクセスできません。</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>不正なパス: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>タイムゾーンを設定できません。</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>リンクの作成に失敗しました、ターゲット: %1 ; リンク名: %2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="95"/>
        <source>Cannot set timezone,</source>
        <translation>タイムゾーンを設定できません,</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation>/etc/timezone を開くことができません</translation>
    </message>
</context>
<context>
    <name>SummaryPage</name>
    <message>
        <location filename="../src/modules/summary/SummaryPage.cpp" line="46"/>
        <source>This is an overview of what will happen once you start the install procedure.</source>
        <translation>これはインストール開始時に行われる事の概要です。</translation>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>要約</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="268"/>
        <source>Your username is too long.</source>
        <translation>ユーザー名が長すぎます。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="278"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation>ユーザー名に不適切な文字が含まれています。アルファベットの小文字と数字のみが使用できます。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="322"/>
        <source>Your hostname is too short.</source>
        <translation>ホスト名が短すぎます。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="333"/>
        <source>Your hostname is too long.</source>
        <translation>ホスト名が長過ぎます。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="344"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>ホスト名に不適切な文字が含まれています。アルファベット、数字及びハイフンのみが使用できます。</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="375"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="408"/>
        <source>Your passwords do not match!</source>
        <translation>パスワードが一致していません！</translation>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
        <source>Users</source>
        <translation>ユーザー情報</translation>
    </message>
</context>
<context>
    <name>WelcomePage</name>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
        <source>Form</source>
        <translation>フォーム</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
        <source>&amp;Language:</source>
        <translation>言語 (&amp;L) :</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation>リリースノート (&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation>既知の問題 (&amp;K)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation>サポート (&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation>説明 (&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="56"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;%1 インストーラーへようこそ。&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="70"/>
        <source>About %1 installer</source>
        <translation>%1 インストーラーについて</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="72"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2015 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;http://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2015 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;http://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="195"/>
        <source>%1 support</source>
        <translation>%1 サポート</translation>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="50"/>
        <source>Welcome</source>
        <translation>ようこそ</translation>
    </message>
</context>
</TS>
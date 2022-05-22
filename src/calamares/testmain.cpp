/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/*
 * This executable loads and runs a Calamares Python module
 * within a C++ application, in order to test the different
 * bindings.
 */

#include "Branding.h"
#include "CppJob.h"
#include "GlobalStorage.h"
#include "Job.h"
#include "JobQueue.h"
#include "Settings.h"
#include "ViewManager.h"
#include "modulesystem/Module.h"
#include "modulesystem/ModuleManager.h"
#include "modulesystem/ViewModule.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Yaml.h"
#include "viewpages/ExecutionViewStep.h"

// Optional features of Calamares
// - Python support
// - QML support
#ifdef WITH_PYTHON
#include "PythonJob.h"
#endif
#ifdef WITH_QML
#include "utils/Qml.h"
#endif


#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QFileInfo>
#include <QLabel>
#include <QMainWindow>
#include <QThread>

#include <memory>

struct ModuleConfig
{
    QString moduleName() const { return m_module; }
    QString configFile() const { return m_jobConfig; }
    QString language() const { return m_language; }
    QString globalConfigFile() const { return m_globalConfig; }

    QString m_module;
    QString m_jobConfig;
    QString m_globalConfig;
    QString m_language;
    QString m_branding;
    bool m_ui;
    bool m_pythonInjection;
};

static ModuleConfig
handle_args( QCoreApplication& a )
{
    QCommandLineOption debugLevelOption(
        QStringLiteral( "D" ), "Verbose output for debugging purposes (0-8), ignored.", "level" );
    QCommandLineOption globalOption( { QStringLiteral( "g" ), QStringLiteral( "global" ) },
                                     QStringLiteral( "Global settings document" ),
                                     "global.yaml" );
    QCommandLineOption jobOption(
        { QStringLiteral( "j" ), QStringLiteral( "job" ) }, QStringLiteral( "Job settings document" ), "job.yaml" );
    QCommandLineOption langOption( { QStringLiteral( "l" ), QStringLiteral( "language" ) },
                                   QStringLiteral( "Language (global)" ),
                                   "languagecode" );
    QCommandLineOption brandOption( { QStringLiteral( "b" ), QStringLiteral( "branding" ) },
                                    QStringLiteral( "Branding directory" ),
                                    "path/to/branding.desc",
                                    "src/branding/default/branding.desc" );
    QCommandLineOption uiOption( { QStringLiteral( "U" ), QStringLiteral( "ui" ) }, QStringLiteral( "Enable UI" ) );
    QCommandLineOption slideshowOption( { QStringLiteral( "s" ), QStringLiteral( "slideshow" ) },
                                        QStringLiteral( "Run slideshow module" ) );
    QCommandLineParser parser;
    parser.setApplicationDescription( "Calamares module tester" );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption( debugLevelOption );
    parser.addOption( globalOption );
    parser.addOption( jobOption );
    parser.addOption( langOption );
    parser.addOption( brandOption );
    parser.addOption( uiOption );
    parser.addOption( slideshowOption );
#ifdef WITH_PYTHON
    QCommandLineOption pythonOption( { QStringLiteral( "P" ), QStringLiteral( "no-injected-python" ) },
                                     QStringLiteral( "Do not disable potentially-harmful Python commands" ) );
    parser.addOption( pythonOption );
#endif

    parser.addPositionalArgument( "module", "Path or name of module to run." );
    parser.addPositionalArgument( "job.yaml", "Path of job settings document to use.", "[job.yaml]" );

    parser.process( a );

    const QStringList args = parser.positionalArguments();
    if ( args.isEmpty() && !parser.isSet( slideshowOption ) )
    {
        cError() << "Missing <module> path.\n";
        parser.showHelp();
    }
    else if ( args.size() > 2 )
    {
        cError() << "More than one <module> path.\n";
        parser.showHelp();
    }
    else
    {
        QString jobSettings( parser.value( jobOption ) );
        if ( jobSettings.isEmpty() && ( args.size() == 2 ) )
        {
            jobSettings = args.at( 1 );
        }

        bool pythonInjection = true;
#ifdef WITH_PYTHON
        if ( parser.isSet( pythonOption ) )
        {
            pythonInjection = false;
        }
#endif
        return ModuleConfig { parser.isSet( slideshowOption ) ? QStringLiteral( "-" ) : args.first(),
                              jobSettings,
                              parser.value( globalOption ),
                              parser.value( langOption ),
                              parser.value( brandOption ),
                              parser.isSet( slideshowOption ) || parser.isSet( uiOption ),
                              pythonInjection };
    }
}

/** @brief Bogus Job for --slideshow option
 *
 * Generally one would use DummyCppJob for this kind of dummy
 * job, but that class lives in a module so isn't available
 * in this test application.
 *
 * This bogus job just sleeps for 3.
 */
class ExecViewJob : public Calamares::CppJob
{
public:
    explicit ExecViewJob( const QString& name, unsigned long t = 3 )
        : m_name( name )
        , m_delay( t )
    {
    }
    ~ExecViewJob() override;

    QString prettyName() const override { return m_name; }

    Calamares::JobResult exec() override
    {
        QThread::sleep( m_delay );
        return Calamares::JobResult::ok();
    }

    void setConfigurationMap( const QVariantMap& ) override {}

private:
    QString m_name;
    unsigned long m_delay;
};

ExecViewJob::~ExecViewJob() {}

/** @brief Bogus module for --slideshow option
 *
 * Normally the slideshow -- displayed by ExecutionViewStep -- is not
 * associated with any particular module in the Calamares configuration.
 * It is added internally by the module manager. For the module-loader
 * testing application, we need something that pretends to be the
 * module for the ExecutionViewStep.
 */
class ExecViewModule : public Calamares::Module
{
public:
    ExecViewModule();
    ~ExecViewModule() override;

    void loadSelf() override;

    virtual Calamares::ModuleSystem::Type type() const override;
    virtual Calamares::ModuleSystem::Interface interface() const override;

    virtual Calamares::JobList jobs() const override;

protected:
    void initFrom( const Calamares::ModuleSystem::Descriptor& ) override;
};

ExecViewModule::ExecViewModule()
    : Calamares::Module()
{
    // Normally the module-loader gives the module an instance key
    // (out of the settings file, or the descriptor of the module).
    // We don't have one, so build one -- this gives us "execView@execView".
    QVariantMap m;
    const QString execView = QStringLiteral( "execView" );
    m.insert( "name", execView );
    Calamares::Module::initFrom( Calamares::ModuleSystem::Descriptor::fromDescriptorData( m, execView ), execView );
}

ExecViewModule::~ExecViewModule() {}

void
ExecViewModule::initFrom( const Calamares::ModuleSystem::Descriptor& )
{
}

void
ExecViewModule::loadSelf()
{
    auto* viewStep = new Calamares::ExecutionViewStep();
    viewStep->setModuleInstanceKey( instanceKey() );
    viewStep->setConfigurationMap( m_configurationMap );
    viewStep->appendJobModuleInstanceKey( instanceKey() );
    Calamares::ViewManager::instance()->addViewStep( viewStep );
    m_loaded = true;
}

Calamares::Module::Type
ExecViewModule::type() const
{
    return Module::Type::View;
}


Calamares::Module::Interface
ExecViewModule::interface() const
{
    return Module::Interface::QtPlugin;
}

Calamares::JobList
ExecViewModule::jobs() const
{
    Calamares::JobList l;
    const auto* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( gs && gs->contains( "jobs" ) )
    {
        QVariantList joblist = gs->value( "jobs" ).toList();
        for ( const auto& jd : joblist )
        {
            QVariantMap jobdescription = jd.toMap();
            if ( jobdescription.contains( "name" ) && jobdescription.contains( "delay" ) )
            {
                l.append( Calamares::job_ptr( new ExecViewJob( jobdescription.value( "name" ).toString(),
                                                               jobdescription.value( "delay" ).toULongLong() ) ) );
            }
        }
    }
    if ( l.count() > 0 )
    {
        return l;
    }

    l.append( Calamares::job_ptr( new ExecViewJob( QStringLiteral( "step 1" ) ) ) );
    l.append( Calamares::job_ptr( new ExecViewJob( QStringLiteral( "step two" ) ) ) );
    l.append( Calamares::job_ptr( new ExecViewJob( QStringLiteral( "locking mutexes" ), 20 ) ) );
    l.append( Calamares::job_ptr( new ExecViewJob( QStringLiteral( "unlocking mutexes" ), 1 ) ) );
    for ( const QString& s : QStringList { "Harder", "Better", "Faster", "Stronger" } )
    {
        l.append( Calamares::job_ptr( new ExecViewJob( s, 0 ) ) );
    }
    l.append( Calamares::job_ptr( new ExecViewJob( QStringLiteral( "cleaning up" ), 20 ) ) );
    return l;
}

static Calamares::Module*
load_module( const ModuleConfig& moduleConfig )
{
    QString moduleName = moduleConfig.moduleName();
    if ( moduleName == "-" )
    {
        return new ExecViewModule;
    }

    QFileInfo fi;  // This is kept around to hold the path of the module descriptor

    bool ok = false;
    QVariantMap descriptor;

    QStringList moduleDirectories { "./", "src/modules/", "modules/", CMAKE_INSTALL_FULL_LIBDIR "/calamares/modules/" };
    for ( const QString& prefix : qAsConst( moduleDirectories ) )
    {
        // Could be a complete path, eg. src/modules/dummycpp/module.desc
        fi = QFileInfo( prefix + moduleName );
        if ( fi.exists() && fi.isFile() )
        {
            descriptor = CalamaresUtils::loadYaml( fi, &ok );
        }
        if ( ok )
        {
            break;
        }

        // Could be a path without module.desc
        fi = QFileInfo( prefix + moduleName );
        if ( fi.exists() && fi.isDir() )
        {
            fi = QFileInfo( prefix + moduleName + "/module.desc" );
            if ( fi.exists() && fi.isFile() )
            {
                descriptor = CalamaresUtils::loadYaml( fi, &ok );
            }
            if ( ok )
            {
                break;
            }
            else
            {
                if ( !fi.exists() )
                {
                    cDebug() << "Expected a descriptor file" << fi.path();
                }
                else
                {
                    cDebug() << "Read descriptor" << fi.path() << "and it was empty.";
                }
            }
        }
    }

    if ( !ok )
    {
        cWarning() << "No suitable module descriptor found in" << Logger::DebugList( moduleDirectories );
        return nullptr;
    }

    QString name = descriptor.value( "name" ).toString();
    if ( name.isEmpty() )
    {
        cWarning() << "No name found in module descriptor" << fi.absoluteFilePath();
        return nullptr;
    }

    QString moduleDirectory = fi.absolutePath();
    QString configFile( moduleConfig.configFile().isEmpty() ? moduleDirectory + '/' + name + ".conf"
                                                            : moduleConfig.configFile() );

    cDebug() << Logger::SubEntry << "Module" << moduleName << "job-configuration:" << configFile;

    Calamares::Module* module = Calamares::moduleFromDescriptor(
        Calamares::ModuleSystem::Descriptor::fromDescriptorData( descriptor, fi.absoluteFilePath() ),
        name,
        configFile,
        moduleDirectory );

    return module;
}

static bool
is_ui_option( const char* s )
{
    return !qstrcmp( s, "--ui" ) || !qstrcmp( s, "-U" );
}

static bool
is_slideshow_option( const char* s )
{
    return !qstrcmp( s, "--slideshow" ) || !qstrcmp( s, "-s" );
}

/** @brief Create the right kind of QApplication
 *
 * Does primitive parsing of argv[] to find the --ui option and returns
 * a UI-enabled application if it does.
 *
 * @p argc must be a reference (to main's argc) because the QCoreApplication
 * constructors take a reference as well, and that would otherwise be a
 * reference to a temporary.
 */
QCoreApplication*
createApplication( int& argc, char* argv[] )
{
    for ( int i = 1; i < argc; ++i )
    {
        if ( is_slideshow_option( argv[ i ] ) || is_ui_option( argv[ i ] ) )
        {
            auto* aw = new QApplication( argc, argv );
            aw->setQuitOnLastWindowClosed( true );
            return aw;
        }
    }
    return new QCoreApplication( argc, argv );
}

#ifdef WITH_PYTHON
static const char pythonPreScript[] = R"%(
# This is Python code executed by Python modules *before* the
# script file (e.g. main.py) is executed.
#
# Calls to suprocess methods that execute something are
# suppressed and logged -- scripts should really be using libcalamares
# methods instead.
_calamares_subprocess = __import__("subprocess", globals(), locals(), [], 0)
import sys
import libcalamares
class fake_subprocess(object):
    PIPE = object()
    STDOUT = object()
    STDERR = object()
    class CompletedProcess(object):
        returncode = 0
        stdout = ""
        stderr = ""
    @staticmethod
    def call(*args, **kwargs):
        libcalamares.utils.debug("subprocess.call(%r,%r) X ignored" % (args, kwargs))
        return 0
    @staticmethod
    def check_call(*args, **kwargs):
        libcalamares.utils.debug("subprocess.check_call(%r,%r) X ignored" % (args, kwargs))
        return 0
    # This is a 3.5-and-later method, is supposed to return a CompletedProcess
    @staticmethod
    def run(*args, **kwargs):
        libcalamares.utils.debug("subprocess.run(%r,%r) X ignored" % (args, kwargs))
        return fake_subprocess.CompletedProcess()
for attr in ("CalledProcessError",):
    setattr(fake_subprocess,attr,getattr(_calamares_subprocess,attr))
sys.modules["subprocess"] = fake_subprocess
libcalamares.utils.debug('pre-script for testing purposes injected')

)%";
#endif

int
main( int argc, char* argv[] )
{
    QCoreApplication* aw = createApplication( argc, argv );

    Logger::setupLogLevel( Logger::LOGVERBOSE );

    ModuleConfig module = handle_args( *aw );
    if ( module.moduleName().isEmpty() )
    {
        return 1;
    }

    std::unique_ptr< Calamares::Settings > settings_p( Calamares::Settings::init( QString() ) );
    std::unique_ptr< Calamares::JobQueue > jobqueue_p( new Calamares::JobQueue( nullptr ) );
    QMainWindow* mw = nullptr;

    auto* gs = jobqueue_p->globalStorage();
    if ( !module.globalConfigFile().isEmpty() )
    {
        gs->loadYaml( module.globalConfigFile() );
    }
    if ( !module.language().isEmpty() )
    {
        QVariantMap vm;
        vm.insert( "LANG", module.language() );
        gs->insert( "localeConf", vm );
    }

#ifdef WITH_PYTHON
    if ( module.m_pythonInjection )
    {
        Calamares::PythonJob::setInjectedPreScript( pythonPreScript );
    }
#endif
#ifdef WITH_QML
    CalamaresUtils::initQmlModulesDir();  // don't care if failed
#endif

    cDebug() << "Calamares module-loader testing" << module.moduleName();
    Calamares::Module* m = load_module( module );
    if ( !m )
    {
        cError() << "Could not load module" << module.moduleName();
        return 1;
    }

    cDebug() << Logger::SubEntry << "got" << m->name() << m->typeString() << m->interfaceString();
    if ( m->type() == Calamares::Module::Type::View )
    {
        // If we forgot the --ui, any ViewModule will core dump as it
        // tries to create the widget **which won't be used anyway**.
        //
        // To avoid that crash, re-create the QApplication, now with GUI
        if ( !qobject_cast< QApplication* >( aw ) )
        {
            auto* replace_app = new QApplication( argc, argv );
            replace_app->setQuitOnLastWindowClosed( true );
            aw = replace_app;
        }
        mw = module.m_ui ? new QMainWindow() : nullptr;
        if ( mw )
        {
            mw->installEventFilter( CalamaresUtils::Retranslator::instance() );
        }

        (void)new Calamares::Branding( module.m_branding );
        auto* modulemanager = new Calamares::ModuleManager( QStringList(), nullptr );
        (void)Calamares::ViewManager::instance( mw );
        modulemanager->addModule( m );
    }

    if ( !m->isLoaded() )
    {
        m->loadSelf();
    }

    if ( !m->isLoaded() )
    {
        cError() << "Module" << module.moduleName() << "could not be loaded.";
        return 1;
    }

    if ( mw )
    {
        auto* vm = Calamares::ViewManager::instance();
        vm->onInitComplete();
        QWidget* w = vm->currentStep()->widget();
        w->setParent( mw );
        mw->setCentralWidget( w );
        w->show();
        mw->show();
        return aw->exec();
    }

    using TR = Logger::DebugRow< const char*, const QString >;

    cDebug() << Logger::SubEntry << "Module metadata" << TR( "name", m->name() ) << TR( "type", m->typeString() )
             << TR( "interface", m->interfaceString() );

    Calamares::JobList jobList = m->jobs();
    unsigned int failure_count = 0;
    unsigned int count = 1;
    for ( const auto& p : jobList )
    {
        // This doesn't get a SubEntry because the jobs may log a bunch of
        // things; print the function-header to make clear that we're back in main.
        cDebug() << "Job #" << count << "name" << p->prettyName();
        Calamares::JobResult r = p->exec();
        if ( !r )
        {
            cError() << "Job #" << count << "failed" << TR( "summary", r.message() ) << TR( "details", r.details() );
            if ( r.errorCode() > 0 )
            {
                ++failure_count;
            }
        }
        ++count;
    }

    if ( aw )
    {
        delete aw;
    }

    return failure_count ? 1 : 0;
}

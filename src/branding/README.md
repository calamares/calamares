# Branding directory

Branding components can go here, or they can be managed and installed separately.

A branding component is a subdirectory with a branding.desc descriptor file, containing brand-specific strings in a key-value structure, plus brand-specific images or QML. Such a subdirectory, when placed here, is automatically picked up by CMake and made available to Calamares.

QML files in a branding component can be translated. Translations should be placed in a subdirectory `lang` of the branding component directory. Qt translation files are supported (`.ts` sources which get compiled into `.qm`). Inside the `lang` subdirectory all translation files must be named according to the scheme `calamares-<component name>_<language>.qm`.

Text in your show.qml should be enclosed in this form for translations `text: qsTr("This is an example text.")`

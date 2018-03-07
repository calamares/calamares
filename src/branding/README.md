# Branding directory

Branding components can go here, or they can be installed separately.

A branding component is a subdirectory with a `branding.desc` descriptor
file, containing brand-specific strings in a key-value structure, plus
brand-specific images or QML. Such a subdirectory, when placed here, is
automatically picked up by CMake and made available to Calamares.

QML files in a branding component can be translated. Translations should
be placed in a subdirectory `lang/` of the branding component directory.
Qt translation files are supported (`.ts` sources which get compiled into
`.qm`). Inside the `lang` subdirectory all translation files must be named
according to the scheme `calamares-<component name>_<language>.qm`.

Text in your `show.qml` (or whatever *slideshow* is set to in the descriptor
file) should be enclosed in this form for translations

```
    text: qsTr("This is an example text.")
```

## Examples

There are two examples of branding content:

 - `default/` is a sample brand for the Generic Linux distribution. It uses
   the default Calamares icons and a as start-page splash it provides a
   tag-cloud view of languages. The slideshow is a basic one with a few
   slides of text and a single image. No translations are provided.
 - `samegame/` is a similarly simple branding setup for Generic Linux,
   but instead of a slideshow, it lets the user play Same Game (clicking
   colored balls) during the installation. The game is taken from the
   QML examples provided by the Qt Company.
 - `fancy/` uses translations and offers navigation arrows.


# Branding directory

Branding components can go here, or they can be installed separately.

A branding component is a subdirectory with a `branding.desc` descriptor
file, containing brand-specific strings in a key-value structure, plus
brand-specific images or QML. Such a subdirectory, when placed here, is
automatically picked up by CMake and made available to Calamares.

It is recommended to package branding separately, so as to avoid
forking Calamares just for adding some files. Calamares installs
CMake support macros to help create branding packages. See the
calamares-branding repository for examples of stand-alone branding.

## Examples

There is one example of a branding component included with Calamares,
so that it can be run directly from the build directory for testing purposes:

 - `default/` is a sample brand for the Generic Linux distribution. It uses
   the default Calamares icons and a as start-page splash it provides a
   tag-cloud view of languages. The slideshow is a basic one with a few
   slides of text and a single image. No translations are provided.

Since the slideshow can be **any** QML, it is limited only by your designers
imagination and your QML experience. For straightforward presentations,
see the documentation below. There are more examples in the *calamares-branding*
repository.

## Translations

QML files in a branding component can be translated. Translations should
be placed in a subdirectory `lang/` of the branding component directory.
Qt translation files are supported (`.ts` sources which get compiled into
`.qm`). Inside the `lang` subdirectory all translation files must be named
according to the scheme `calamares-<component name>_<language>.ts`.

Text in your `show.qml` (or whatever *slideshow* is set to in the descriptor
file) should be enclosed in this form for translations

```
    text: qsTr("This is an example text.")
```

## Presentation

The default QML classes provided by Calamares can be used for a simple
and straightforward "slideshow" presentation with static text and
pictures. To use the default slideshow classes, start with a `show.qml`
file with the following content:

```
import QtQuick 2.5;
import calamares.slideshow 1.0;

Presentation
{
    id: presentation
}
```

After the *id*, set properties of the presentation as a whole. These include:
 - *loopSlides* (default true) When set, clicking past the last slide
   returns to the very first slide.
 - *mouseNavigation*, *arrowNavigation*, *keyShortcutsEnabled* (all default
   true) enable different ways to navigate the slideshow.
 - *titleColor*, *textColor* change the look of the presentation.
 - *fontFamily*, *codeFontFamily* change the look of text in the presentation.

After setting properties, you can add elements to the presentation.
Generally, you will add a few presentation-level elements first,
then slides.
 - For visible navigation arrows, add elements of class *ForwardButton* and
   *BackwardButton*. Set the *source* property of each to a suitable
   image. See the `fancy/` example. It is recommended to turn off other
   kinds of navigation when visible navigation is used.
 - To indicate where the user is, add an element of class *SlideCounter*.
   This indicates in "n / total" form where the user is in the slideshow.
 - To automatically advance the presentation (for a fully passive slideshow),
   add a timer that calls the `goToNextSlide()` function of the presentation.
   See the `default/` example -- remember to start the timer when the
   presentation is completely loaded.

After setting the presentation elements, add one or more Slide elements.
The presentation framework will make a slideshow out of the Slide
elements, displaying only one at a time. Each slide is an element in itself,
so you can put whatever visual elements you like in the slide. They have
standard properties for a boring "static text" slideshow, though:
 - *title* is text to show as slide title
 - *centeredText* is displayed in a large-ish font
 - *writeInText* is displayed by "writing it in" to the slide,
   one letter at a time.
 - *content* is a list of things which are displayed as a bulleted list.

The presentation classes can be used to produce a fairly dry slideshow
for the installation process; it is recommended to experiment with the
visual effects and classes available in QtQuick.

## Project Layout

A branding component that is created and installed outside of Calamares
will have a top-level `CMakeLists.txt` that includes some boilerplate
to find Calamares, and then adds a subdirectory which contains the
actual branding component.

Adding the subdirectory can be done as follows:

 - If the directory contains files only, and optionally has a single
   subdirectory lang/ which contains the translation files for the
   component, then `calamares_add_branding_subdirectory()` can be
   used, which takes only the name of the subdirectory.

The file layout in a typical branding component repository is:

```
 /
 - CMakeLists.txt
 - componentname/
   - show.qml
   - image1.png
   ...
   - lang/
     - calamares-componentname_en.ts
     - calamares-componentname_de.ts
     ...
```

 - If the branding component has many files which are organized into
   subdirectories, use the SUBDIRECTORIES argument to the CMake function
   to additionally install files from those subdirectories. For example,
   if the component places all of its images in an `img/` subdirectory,
   then call `calamares_add_branding_subdirectory( ... SUBDIRECTORIES img)`.
   It is a bad idea to include `lang/` in the SUBDIRECTORIES list.

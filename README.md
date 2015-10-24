## Building

You need:

* Qt 5.6 alpha
* cmake 3.0 or newer
* ninja is recommended for building

Special Qt requirements:

* On Windows, you must apply ``qt-patches/0003-Always-enable-viewport-stuff.patch``
  for correct window scaling. The patches in ``qt-patches/qt-5.6-alpha/`` fix
  some stability issues.
* On OSX, you should apply ``qt-patches/0002-qtbase-Don-t-show-the-menu-bar-at-all-in-lion-style-fullscr.patch``
  to improve the user experience in fullscreen.
* You can try to use Qt 5.5, but then you also need to apply the following patches:
    - ``qt-patches/0001-qtwebengine-Add-a-backgroundColor-property.patch``
    - ``qt-patches/0004-qtwebengine-transparency-window-creation.patch``

  Without them, video playback will not work.

## Building on Mac OS X

Get dependencies:

* ``scripts/fetch-binaries.py -p darwin-x86_64``

If you're happy just building from the command line then run CMake for the ninja build tool:

* ``mkdir build ; cd build``
* ``cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DQTROOT=/path/to/qt -DCMAKE_INSTALL_PREFIX=output ..``

Build (ninja):

* ``ninja``

Make a distributable package:

* ``ninja install`` (be patient, it's slow)

Or if you prefer working in Xcode, run CMake for the xcode build):

* ``mkdir build ; cd build``
* ``cmake -GXcode -DQTROOT=/path/to/qt ..``

## Building on Linux

### Building Qt 5.6.0 alpha

You'll want to grab one of the Qt 5.6.0 alpha packages from http://download.qt.io/development_releases/qt/5.6/5.6.0-alpha/single/ and unpack it locally. On Fedora, even with a working development environment set up, the following packages were necessary to successfully build Qt (and QtWebEngine):

Fedora users:
```
sudo dnf install libxcb libxcb-devel libXrender libXrender-devel xcb-util-wm xcb-util-wm-devel xcb-util xcb-util-devel xcb-util-image xcb-util-image-devel xcb-util-keysyms xcb-util-keysyms-devel libcap-devel snappy-devel libsrtp-devel nss-devel pciutils-devel gperf
```

Debian users
```	
sudo apt-get install libfontconfig1-dev libfreetype6-dev libx11-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libx11-xcb-dev libxcb-glx0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync0-dev libxcb-xfixes0-dev libxcb-shape0-dev	libxcb-randr0-dev libxcb-render-util0-dev
```

(The majority of the packages on this list came from http://code.qt.io/cgit/qt/qtbase.git/tree/src/plugins/platforms/xcb/README, but everything after xcb-util-keysyms-devel was trial-and-error in attempts build QtWebEngine; this list of packages may not be complete, but hopefully it provides a useful starting point.)

Once you've unpacked the Qt 5.6.0 alpha package:

* ``cd qt-everywhere-opensource-src-5.6.0-alpha``
* ``./configure -confirm-license -opensource``
* ``make``
* ``sudo make install``
* ``cd qtwebengine``
* ``qmake``
* ``make``
* ``sudo make install``

That should do it for Qt. It's worth noting that, on a Core i7-950 with 24GB of RAM, this took more than three hours to build.

### Building mpv

mpv is a bit easier to build than Qt, and compiles much faster.

Before you attempt to build mpv, make sure you have either ffmpeg 2.4.0 (and related development packages) or libav11 (and related devel packages) installed.

* ``git clone git://github.com/mpv-player/mpv``
* ``cd mpv``
* ``./bootstrap.py``
* ``./waf configure --enable-libmpv-shared``
* ``./waf build``
* ``sudo ./waf install``

### Finally! Building plex-media-player

Assuming that everything else has installed correctly, building Plex Media Player should now be fairly straightforward:

* ``git clone git://github.com/plexinc/plex-media-player``
* ``cd plex-media-player``
* ``mkdir build``
* ``cd build``
* ``cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DQTROOT=/usr/local/Qt-5.6.0 -DMPV_INCLUDE_DIR=/usr/local/include/mpv -DMPV_LIBRARY=/usr/local/lib/libmpv.so.1 -DCMAKE_INSTALL_PREFIX=output ..``
* ``ninja-build``

Once ninja-build completes successfully, you should have a usable ``./src/plexmediaplayer`` binary. Run it and test it out! If it works as you expect, you should be able to run ``sudo install ./src/plexmediaplayer ./src/pmphelper /usr/local/bin`` so that the program is usable from anywhere on the system.

## License

Plex Media Player is licensed under GPL v2. See the ``LICENSE`` file.
Licenses of dependencies are summarized under ``resources/misc/licenses.txt``.
This file can also be printed at runtime when using the ``--licenses`` option.


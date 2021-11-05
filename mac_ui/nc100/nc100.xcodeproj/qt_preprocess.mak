#############################################################################
# Makefile for building: nc100.app/Contents/MacOS/nc100
# Generated by qmake (3.1) (Qt 6.2.0)
# Project:  nc100.pro
# Template: app
# Command: /Users/petrvanek/Qt/6.2.0/macos/bin/qmake -o nc100.xcodeproj/project.pbxproj nc100.pro -spec macx-xcode
#############################################################################

MAKEFILE      = project.pbxproj

EQ            = =

MOC       = /Users/petrvanek/Qt/6.2.0/macos/libexec/moc
UIC       = /Users/petrvanek/Qt/6.2.0/macos/libexec/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
INCPATH       = -I. -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtWidgets.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtGui.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/AGL.framework/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/AGL.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/mkspecs/macx-clang -F/Users/petrvanek/Qt/6.2.0/macos/lib
DEL_FILE  = rm -f
MOVE      = mv -f

preprocess: compilers
clean preprocess_clean: compiler_clean

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compilers: moc_file_transfer_worker.cpp moc_formheddump.cpp moc_widget.cpp ui_formheddump.h ui_widget.h
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all: moc_file_transfer_worker.cpp moc_formheddump.cpp moc_widget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_file_transfer_worker.cpp moc_formheddump.cpp moc_widget.cpp
moc_file_transfer_worker.cpp: file_transfer_worker.h \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QObject \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QMetaType \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QThread \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QMutex \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QWaitCondition \
		../../include/serial_intf.h \
		/Users/petrvanek/Qt/6.2.0/macos/libexec/moc
	/Users/petrvanek/Qt/6.2.0/macos/libexec/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 -D__APPLE_CC__ -D__cplusplus=199711L -D__APPLE_CC__=6000 -D__clang__ -D__clang_major__=13 -D__clang_minor__=0 -D__clang_patchlevel__=0 -D__GNUC__=4 -D__GNUC_MINOR__=2 -D__GNUC_PATCHLEVEL__=1 -I/Users/petrvanek/Qt/6.2.0/macos/mkspecs/macx-clang -I/Users/petrvanek/Documents/development/nc100/mac_ui/nc100 -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtWidgets.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtGui.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1 -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/13.0.0/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include -F/Users/petrvanek/Qt/6.2.0/macos/lib file_transfer_worker.h -o moc_file_transfer_worker.cpp

moc_formheddump.cpp: formheddump.h \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtWidgets.framework/Headers/QWidget \
		/Users/petrvanek/Qt/6.2.0/macos/libexec/moc
	/Users/petrvanek/Qt/6.2.0/macos/libexec/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 -D__APPLE_CC__ -D__cplusplus=199711L -D__APPLE_CC__=6000 -D__clang__ -D__clang_major__=13 -D__clang_minor__=0 -D__clang_patchlevel__=0 -D__GNUC__=4 -D__GNUC_MINOR__=2 -D__GNUC_PATCHLEVEL__=1 -I/Users/petrvanek/Qt/6.2.0/macos/mkspecs/macx-clang -I/Users/petrvanek/Documents/development/nc100/mac_ui/nc100 -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtWidgets.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtGui.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1 -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/13.0.0/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include -F/Users/petrvanek/Qt/6.2.0/macos/lib formheddump.h -o moc_formheddump.cpp

moc_widget.cpp: widget.h \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtWidgets.framework/Headers/QWidget \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QStringListModel \
		file_transfer_worker.h \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QObject \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QMetaType \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QThread \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QMutex \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QWaitCondition \
		../../include/serial_intf.h \
		../../include/crosstypes.h \
		../../include/serial_enumerator_intf.h \
		../../include/hex_stream_formatter.h \
		../../include/modem.h \
		../../utils/dirs.h \
		../../utils/file.h \
		configuration.h \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QSettings \
		/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers/QString \
		/Users/petrvanek/Qt/6.2.0/macos/libexec/moc
	/Users/petrvanek/Qt/6.2.0/macos/libexec/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 -D__APPLE_CC__ -D__cplusplus=199711L -D__APPLE_CC__=6000 -D__clang__ -D__clang_major__=13 -D__clang_minor__=0 -D__clang_patchlevel__=0 -D__GNUC__=4 -D__GNUC_MINOR__=2 -D__GNUC_PATCHLEVEL__=1 -I/Users/petrvanek/Qt/6.2.0/macos/mkspecs/macx-clang -I/Users/petrvanek/Documents/development/nc100/mac_ui/nc100 -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtWidgets.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtGui.framework/Headers -I/Users/petrvanek/Qt/6.2.0/macos/lib/QtCore.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1 -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/13.0.0/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include -F/Users/petrvanek/Qt/6.2.0/macos/lib widget.h -o moc_widget.cpp

compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_formheddump.h ui_widget.h
compiler_uic_clean:
	-$(DEL_FILE) ui_formheddump.h ui_widget.h
ui_formheddump.h: formheddump.ui \
		/Users/petrvanek/Qt/6.2.0/macos/libexec/uic
	/Users/petrvanek/Qt/6.2.0/macos/libexec/uic formheddump.ui -o ui_formheddump.h

ui_widget.h: widget.ui \
		/Users/petrvanek/Qt/6.2.0/macos/libexec/uic
	/Users/petrvanek/Qt/6.2.0/macos/libexec/uic widget.ui -o ui_widget.h

compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

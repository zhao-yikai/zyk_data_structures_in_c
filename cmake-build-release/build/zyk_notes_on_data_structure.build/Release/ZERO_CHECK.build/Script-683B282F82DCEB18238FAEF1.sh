#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release
  make -f /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release
  make -f /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release
  make -f /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release
  make -f /Users/augustinzhao/Desktop/code/zyk_notes_on_data_structure/cmake-build-release/CMakeScripts/ReRunCMake.make
fi


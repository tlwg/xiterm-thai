Summary: xiterm with Thai patch
Name: xiterm+thai
Version: 1.04pre1
Release: 1
Copyright: GPL
Group: Extensions/Thai
Source0: %{name}-%{version}.tar.gz
Source1: txiterm
Source2: txiterm.desktop
Source3: Txiterm.kdelnk
BuildRoot: /var/tmp/%{name}-%{version}-root
URL: http://zzzthai.fedu.uec.ac.jp/linux
Distribution: Linux TLE, Thai Linux Working Group
Vendor: Modified by Vuthichai Ampornaramvech <vuthi@venus.dti.ne.jp>
Packager: Theppitak Karoonboonyanan <thep@links.nectec.or.th>
Requires: thaixfonts >= 1.1-3


%description
This package was modified from xiterm to use Thai language with xterm. 
You can switch to Thai keyboard by pressing Ctrl+Space or F1. 
Using Thai X terminal with command "txiterm".

%prep
%setup

%build
./configure --prefix=/usr
make


%install
mkdir -p $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

install -D -m 755 %{SOURCE1} $RPM_BUILD_ROOT/usr/bin/%{SOURCE1}
# mHom: install menu.
install -D -m 644 %{SOURCE2} $RPM_BUILD_ROOT/usr/share/gnome/apps/Utilities/txiterm.desktop
install -D -m 644 %{SOURCE3} $RPM_BUILD_ROOT/etc/skel/Desktop/Txiterm.kdelnk

%clean
rm -fr $RPM_BUILD_DIR/%{name}-%{version}
rm -fr $RPM_BUILD_ROOT/%{name}-%{version}-root


%post

%postun


%files
%doc README
%doc README.thai
/usr/bin/xiterm
/usr/bin/txiterm
/usr/man/man1/xiterm.1
/usr/share/gnome/apps/Utilities/txiterm.desktop
/etc/skel/Desktop/Txiterm.kdelnk

%changelog
* Fri Jan 19 2001 Theppitak Karoonboonyanan <thep@links.nectec.or.th>
- fix path for xiterm in txiterm script (Thnx: Pattara Kiatisevi)
- fix install script for GNOME menu installation (Thnx: Sadit Sathianpaisarn)
- add %clean script to clear RPM_BUILD_ROOT (Thnx: Sadit Sathianpaisarn)
- add KDE link (Thnx: Sadit Sathianpaisarn)

* Mon Jan 01 2001 Theppitak Karoonboonyanan <thep@links.nectec.or.th>
- xiterm+thai.spec : use variables for sources, path names; use BuildRoot
- xiterm+thai.spec : use /usr prefix instead of /usr/local
- release version 1.04pre1

* Sat Nov 18 2000 Theppitak Karoonboonyanan <thep@links.nectec.or.th>
- src/command.c : Add XSetICFocus() to force initialization of Input_Context
  which is necessary for XIM tasks.
- src/command.c, src/xdefaults.c : Add -tim option (thai_im resource) for
  specifying Thai XIM mode.
	  
* Thu Nov 09 2000 Theppitak Karoonboonyanan <thep@links.nectec.or.th>
- add setlocale() as per Lucy's contribution to support new Thai XKB map
  of XFree86 4.0.1 which conforms to <X11/keysymdef.h>
- release version 1.03

* Tue Jul 06 1999 Pattara Kiatisevi <ott@nectec.or.th>
- modify "txiterm" shell script to pass arguments to "xiterm" if any.

* Thu Jul 01 1999 Poonlap Veerathanabutr <poon-v@fedu.uec.ac.jp>
- re-write spec file
- create shell script for txiterm
- use nectec18 font


%define name    stella
%define version 2.2
%define rel     1

%define build_plf 0

%define enable_gl 1
%define enable_sound 1
%define enable_developer 1
%define enable_snapshot 1
%define enable_joystick 1
%define enable_cheats 1
%define enable_static 0

%if %build_plf
  %define release %mkrel %rel
  %define distsuffix plf
%else
  %define release %rel
%endif

Summary:        An Atari 2600 Video Computer System emulator
Name:           %{name}
Version:        %{version}
Release:        %{release}
Group:          Emulators
License:        GPL
URL:            http://stella.sourceforge.net
Source:         %{name}-%{version}.tar.bz2
BuildRoot:      %_tmppath/%name-%version-%release-root
BuildRequires:  SDL-devel
BuildRequires:  MesaGLU-devel
BuildRequires:  zlib-devel

%description
The Atari 2600 Video Computer System (VCS), introduced in 1977, was the most
popular home video game system of the early 1980's.  This emulator will run
most Atari ROM images, so that you can play your favorite old Atari 2600 games
on your PC.
%if %build_plf
This package is in PLF as Mandriva Linux policy forbids emulators in contribs.
%endif

%prep

%setup -q

%build
export CXXFLAGS=$RPM_OPT_FLAGS
%configure \
%if %enable_gl
  --enable-gl \
%else
  --disable-gl \
%endif
%if %enable_sound
  --enable-sound \
%else
  --disable-sound \
%endif
%if %enable_developer
  --enable-developer \
%else
  --disable-developer \
%endif
%if %enable_snapshot
  --enable-snapshot \
%else
   --disable-snapshot \
%endif
%if %enable_joystick
  --enable-joystick \
%else
  --disable-joystick \
%endif
%if %enable_cheats
  --enable-cheats \
%else
  --disable-cheats \
%endif
%if %enable_static
  --enable-static \
%else
  --enable-shared \
%endif
  --docdir=%{_docdir}/stella \
  --x-libraries=%{_prefix}/X11R6/%{_lib}

%make

%install
rm -rf $RPM_BUILD_ROOT

make install-strip DESTDIR=%{buildroot}
# Mandriva menu entries
install -d -m0755 %{buildroot}%{_menudir}
cat > %{buildroot}%{_menudir}/%{name} << EOF
?package(%{name}): command="stella" \
icon="stella.xpm" \
needs="x11" \
title="Stella" \
longtitle="A multi-platform Atari 2600 emulator" \
section="More Applications/Emulators" \
xdg="true"
EOF

%clean
rm -rf $RPM_BUILD_ROOT
rm -rf $RPM_BUILD_DIR/%{name}-%{version}

%post
%update_menus

%postun
%clean_menus

%files
%defattr(-,root,root,-)
%_bindir/*
%{_menudir}/%{name}
%{_datadir}/applications/%{name}.desktop
%_docdir/stella/*
%_datadir/icons/%{name}.xpm
%_datadir/icons/mini/%{name}.xpm
%_datadir/icons/large/%{name}.xpm

%changelog
* Fri Sep 08 2006 Stephen Anthony <stephena@zarb.org> 2.2-1plf2007.0
- Packaged 2.2 release for PLF
- Added XDG menu

* Sat Oct 29 2005 Stephen Anthony <stephena@zarb.org> 2.0.1-3plf
- Fix for x86_64 compilation

* Wed Oct 26 2005 Stephen Anthony <stephena@zarb.org> 2.0.1-2plf
- Fix for improper PLF upload

* Sun Oct 24 2005 Stephen Anthony <stephena@zarb.org> 2.0.1-1
- Version 2.0.1 release, and plaform-agnostic SRPM (hopefully)

* Sun Oct  9 2005 Stefan van der Eijk <stefan@eijk.nu> 1.4.2-3plf
- BuildRequires
- distsuffix & mkrel

* Sun Jul 31 2005 Stephen Anthony <stephena@zarb.org> 1.4.2-2plf
- Recompile for distro name change

* Sat Feb 19 2005 Stephen Anthony <stephena@zarb.org> 1.4.2-1plf
- 1.4.2
- First release of Stella 1.4.2 for PLF

* Sat Apr 24 2004 Stefan van der Eijk <stefan@eijk.nu> 1.3-1plf
- 1.3
- remove stella sound, seems to be included?

* Sun Nov 10 2002 Stefan van der Eijk <stefan@eijk.nu> 1.2-3plf
- BuildRequires

* Thu Oct 24 2002 Olivier Thauvin <thauvin@aerov.jussieu.fr> 1.2-2plf 
- by Rob Kudla <rpm@kudla.org>
- doh!  forgot to build the sound server!

* Wed Oct 22 2002 Rob Kudla <rpm@kudla.org> 1.2-1plf
- oh yeah, I guess emulators go in plf

* Tue Oct 22 2002 Rob Kudla <rpm@kudla.org> 1.2-1mdk
- first attempt at package

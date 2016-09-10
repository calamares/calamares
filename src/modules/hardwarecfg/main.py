#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Philip Müller <philm@manjaro.org>
#
#   Calamares is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Calamares is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Calamares. If not, see <http://www.gnu.org/licenses/>.

import os
import subprocess

import libcalamares

import shutil

def run():
    """ Configure the hardware """

    install_path = libcalamares.globalstorage.value( "rootMountPoint" )

    # Copy generated xorg.xonf to target
    if os.path.exists("/etc/X11/xorg.conf"):
        shutil.copy2('/etc/X11/xorg.conf',
             os.path.join(install_path, 'etc/X11/xorg.conf'))

    # TODO: Maybe we can drop this
    # Configure ALSA
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Master 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Front 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Side 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Surround 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Center 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset LFE 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Headphone 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Speaker 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset PCM 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Line 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset External 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset FM 50% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Master Mono 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Master Digital 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Analog Mix 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Aux 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Aux2 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset PCM Center 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset PCM Front 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset PCM LFE 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset PCM Side 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset PCM Surround 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Playback 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset PCM,1 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset DAC 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset DAC,0 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset DAC,1 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Synth 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset CD 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Wave 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Music 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset AC97 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Analog Front 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset VIA DXS,0 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset VIA DXS,1 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset VIA DXS,2 70% unmute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset VIA DXS,3 70% unmute'])

    # set input levels
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Mic 70% mute'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset IEC958 70% mute'])

    # special stuff
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Master Playback Switch on'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Master Surround on'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset SB Live Analog/Digital Output Jack off'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Audigy Analog/Digital Output Jack off'])

    # special stuff
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Master Playback Switch on'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Master Surround on'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset SB Live Analog/Digital Output Jack off'])
    libcalamares.utils.target_env_call(['sh', '-c', 'amixer -c 0 sset Audigy Analog/Digital Output Jack off'])

    # Set pulse
    if os.path.exists("/usr/bin/pulseaudio-ctl"):
        libcalamares.utils.target_env_call(['pulseaudio-ctl', 'normal'])

    # Save settings
    libcalamares.utils.target_env_call(['alsactl', '-f', '/etc/asound.state', 'store'])

    if os.path.exists("/opt/livecd"):
        repo_path="/opt/livecd/pacman-gfx.conf"
    else:
        repo_path="/opt/live/pacman-gfx.conf"

    # Install xf86-video driver
    if os.path.exists(repo_path):
        # TODO: get mhwd-script path or port it to python
        mhwd_script_path = '/usr/lib/calamares/modules/hardwarecfg/mhwd.sh'
        #try:
        subprocess.check_call(["/usr/bin/bash", mhwd_script_path, install_path])

    # Remove virtualbox driver on real hardware
    p1 = subprocess.Popen(["mhwd"], stdout=subprocess.PIPE)
    p2 = subprocess.Popen(["grep", "0300:80ee:beef"], stdin=p1.stdout, stdout=subprocess.PIPE)
    num_res = p2.communicate()[0]
    if num_res == "0":
        libcalamares.utils.target_env_call(['sh', '-c', 'pacman -Rsc --noconfirm $(pacman -Qq | grep virtualbox-guest-modules)'])

    return None

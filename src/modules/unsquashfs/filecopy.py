#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
#
#   Originally from Cnchi and Thus,
#   Copyright 2013 Antergos (http://antergos.com/)
#   Copyright 2013 Manjaro (http://manjaro.org)
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

import sys
import os
import subprocess
import re

from threading import Thread


COPY_CMD = 'rsync -ar --progress %(source)s %(dest)s'
ON_POSIX = 'posix' in sys.builtin_module_names


class FileCopyThread( Thread ):
    """ Update the value of the progress bar so that we get some movement """
    def __init__( self, source, dest, progress_cb ):
        # Environment used for executing rsync properly
        # Setting locale to C (fix issue with tr_TR locale)
        self.at_env = os.environ
        self.at_env["LC_ALL"] = "C"

        self.process = subprocess.Popen(
            ( COPY_CMD % {
                'source': source,
                'dest': dest,
                } ).split(),
            env=self.at_env,
            bufsize=1,
            stdout=subprocess.PIPE,
            close_fds=ON_POSIX
        )

        self.progress_cb = progress_cb

        super( FileCopyThread, self ).__init__()


    def kill( self ):
        if self.process.poll() is None:
            self.process.kill()


    def run( self ):
        num_files_copied = 0
        for line in iter( self.process.stdout.readline, b'' ):
            # small comment on this regexp.
            # rsync outputs three parameters in the progress.
            # xfer#x => i try to interpret it as 'file copy try no. x'
            # to-check=x/y, where:
            #  - x = number of files yet to be checked
            #  - y = currently calculated total number of files.
            # but if you're copying directory with some links in it, the xfer# might not be a
            # reliable counter. ( for one increase of xfer, many files may be created)
            # In case of manjaro, we pre-compute the total number of files.
            # therefore we can easily subtract x from y in order to get real files copied / processed count.
            m = re.findall( r'xfr#(\d+), ir-chk=(\d+)/(\d+)', line.decode() )
            if m:
                # we've got a percentage update
                num_files_remaining = int(m[0][1])
                num_files_total_local = int(m[0][2])
                # adjusting the offset so that progressbar can be continuesly drawn
                num_files_copied = num_files_total_local - num_files_remaining


                # I guess we're updating every 100 files...
                if num_files_copied % 100 == 0:
                    self.progress_cb( num_files_copied )

#!/usr/bin/env python3

import libcalamares



def run():
    """
    Sets global storage variable for ARM installs

    """

    libcalamares.globalstorage.insert("arm_install", True)

    libcalamares.job.setprogress(1.0)

    return None

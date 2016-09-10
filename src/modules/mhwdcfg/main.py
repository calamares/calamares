#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2016, Artoo <artoo@manjaro.org>
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

import libcalamares

from libcalamares.utils import check_target_env_call, target_env_call, debug
from os.path import join
from subprocess import check_call, call

class MhwdController:
	def __init__(self):
		self.__root = libcalamares.globalstorage.value( "rootMountPoint" )
		self.__bus = libcalamares.job.configuration.get('bus', [])
		self.__identifier = libcalamares.job.configuration.get('identifier', [])
		self.__local = libcalamares.job.configuration['local']
		self.__repo = libcalamares.job.configuration['repo']
		self._driver = libcalamares.job.configuration['driver']

	@property
	def driver(self):
		return self._driver

	@driver.setter
	def driver(self, value):
		self._driver = value
		
	@property
	def root(self):
		return self.__root

	@property
	def local(self):
		return self.__local
	
	@property
	def repo(self):
		return self.__repo
	
	@property
	def identifier(self):
		return self.__identifier
	
	@property
	def bus(self):
		return self.__bus
	
	def umount(self, mp):
		call(["umount", "-l", join(self.root, mp)])
		
	def mount(self, mp):
		call(["mount", "-Br", "/" + mp, join(self.root, mp)])
	
	def configure(self, name, id):
		cmd = ["mhwd", "-a", str(name), str(self.driver), str(id).zfill(4)]
		if self.local:
			self.mount("opt")
			cmd.extend(["--pmconfig", self.repo])
			
		self.mount("etc/resolv.conf")
		check_target_env_call(cmd)
		
		if self.local:
			self.umount("opt")
		self.umount("etc/resolv.conf")
		
	def run(self):
		for id in self.identifier['net']:
			for b in self.bus:
				self.configure(b, id)
		for id in self.identifier['video']:
			for b in self.bus:
				self.configure(b, id)
				
		return None

def run():
	""" Configure the hardware """

	mhwd = MhwdController()
	
	return mhwd.run()

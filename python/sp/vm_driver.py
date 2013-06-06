#!/usr/bin/env python
################################################################################
################################################################################
#
# Authors: Jarret Shook
#
# Module: vm_util.py
#
# Modifications: 
#
# 28-May-13: Version 1.0: Created
#
# Timeperiod: ev6
#
# Notes:
#
#     The Background script provided must have an script_entry_point function
#     defined
#
################################################################################
################################################################################

from vm_util import *

import sys

################################################################################
################################################################################

# path to virtual machine
# number of concurrent machines
# directory of startup file

def determine_parameters():

   def _check_parameter(_Parameter):

      # -v = virtual machine
      # -d = destination
      # -c = number of concurrent machines
      # -s = startup file
      # -bs = background script
      # --help = help

      if _Parameter == "-v": return True

      elif _Parameter == "-d": return True

      elif _Parameter == "-c": return True

      elif _Parameter == "-s": return True

      elif _Parameter == "-bs": return True

      elif _Parameter == "--help": return True

      else: return False

   _Parameters = list()

   for _Item in range(5):

      _Parameters.append(None);

   _LastParameter = None

   _Args = sys.argv[1:] # ignore the first arguement

   _Next = False

   for _Parameter in _Args:

      if (_check_parameter(_Parameter)):

         if _Parameter == "--help": 

            print_help()

            exit() # in case there were more parameters

         else: 

            _LastParameter = _Parameter

            _Next = True

      else:

         if _Next:

            _Next = False

            if (_LastParameter == "-v"): _Parameters[0] = _Parameter
         
            elif (_LastParameter == "-c"): _Parameters[1] = _Parameter

            elif (_LastParameter == "-s"): _Parameters[2] = _Parameter

            elif (_LastParameter == "-bs"): _Parameters[3] = _Parameter

            elif (_LastParameter == "-d"): _Parameters[4] = _Parameter

            else:

               print "Incorrect parameter try using --help"

               return None

         else:

            print "Incorrect formatting of parameters, recheck syntax"

            exit()

   if _Next:

      print "Incorrect formatting of parameters, recheck syntax"

      exit()

   return _Parameters

def main(_VirtualMachine, _Destination, _NumberOfMachines, _StartupFile, _BackgroundScript):

   if _VirtualMachine == None: 

      print "Error you must provide a Virtual Machine's directory at a minimum"

      exit()

   if _Destination == None:

      print "Error you must provide a Virtual Machine's directory at a minimum"

      exit()

   elif _StartupFile == None and _BackgroundScript == None:

      start_machines(_VirtualMachine, _NumberOfMachines, _StartupFile, _BackgroundScript, False, False)

   elif _StartupFile == None and _BackgroundScript != None:

      start_machines(_VirtualMachine, _NumberOfMachines, _StartupFile, _BackgroundScript, False, True)

   elif _StartupFile != None and _BackgroundScript != None:

      start_machines(_VirtualMachine, _NumberOfMachines, _StartupFile, _BackgroundScript, True, True)

def print_help():

   print "Commands:"

   print ""

   print "-v path to a vmware virtual machine folder to clone"

   print "-d destination folder"

   print "-s path to a startup file that will be run on the cloned machine"

   print "-bs path to a script to be run in the background while a vm machine is running"

   print "-c amount of concurrent machines"

   print "--help help"

def start_machines(_VirtualMachine, _Destination, _NumberOfMachines, _StartupFile, _BackgroundScript, _IsStartupFile, _IsBackgroundScript):

   _NewVmdk = _NewMachineName + ".vmdk"

   _NewVmx = _NewMachineName + ".vmx"

   for _Number in range(_NumberOfMachines):

      if not _IsStartupFile: _ClonedMachine = vmware_create(_VirtualMachine, _Destination, _NewVmx, _NewVmdk)

      else: vmware_create(_VirtualMachine, _Destination, _NewVmx, _NewVmdk)

if __name__ == '__main__':

   _Parameters = determine_parameters()  

   _VirtualMachine = None

   _Destination = None

   _NumberOfMachines = 0

   _StartupFile = None
   
   _Script = None

   if len(sys.argv) == 1: 

      print "Incorrect amount of parameters, try --help for more information"

      exit()

   if _Parameters == None: exit()

   if _Parameters[0] != None:

      _VirtualMachine = _Parameters[0]

   if _Parameters[2] != None:

      _Script = _Parameters[2]

   if _Parameters[3] != None:

      _NumberOfMachines = _Parameters[3]

   if _Parameters[1] != None:

      _StartupFile = _Parameters[1]

   main(_VirtualMachine, _Destination, _NumberOfMachines, _StartupFile, _Script)

   # go through the list of threads and join them to the main thread

   vmware_join()

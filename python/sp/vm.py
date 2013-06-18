################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: vm.py
#
# Modifications:
#
# 17-June-13: Version 1.0: Last Updated
# 25-May-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

from vm_util import *

from entry import *

################################################################################
################################################################################

class vm:

   def __call__(_Self):

      if _Self._m_function is not None: _Self._m_function(_Self)

   def __init__(_Self, _Directory = None, _ConfigFile = None, _DiskFile = None, _StartupFile = None, _ConfigCreated = False, _DiskCreated = False):

      ####################################################
      # Member Variables
      ####################################################

      _Self._m_directory = _Directory
      _Self._m_mount_directory = _Directory + "mnt/"
      _Self._m_config_file = _ConfigFile
      _Self._m_disk_file = _DiskFile
      _Self._m_disk_created = _ConfigCreated
      _Self._m_config_created = _DiskCreated
      _Self._m_function = None
      _Self._m_startup_file = _StartupFile
      _Self._m_thread = None

   def disk_created(_Self):

      return _Self._m_disk_created

   def config_created(_Self):

      return _Self._m_config_created

   def set_directory(_Self, _Directory):

      _Self._m_directory = _Directory

   def set_disk(_Self, _DiskFile):

      _Self._m_disk_file = _DiskFile

   def set_config(_Self, _ConfigFile):

      _Self._m_config_file = _ConfigFile

   def set_disk_created(_Self, _Created):

      _Self._m_disk_created = _Created

   def set_config_created(_Self, _Created):

      _Self._m_config_created = _Created

   def set_function(_Self, _Function):

      _Self._m_function = _Function

   def set_startup_file(_Self, _File):

      _Self._m_startup_file = _File

   def pre_run_function(_Self):

      vmware_pre_run(_Self)

   def post_run_function(_Self):

      vmware_post_run(_Self)

################################################################################
################################################################################
#
# End of class vm
#
################################################################################
################################################################################

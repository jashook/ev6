################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: vm.py
#
# Modifications:
#
# 25-May-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

class vm:

   def __init__(_Self, _Directory = None, _ConfigFile = None, _DiskFile = None, _ConfigCreated = False, _DiskCreated = False):

      ####################################################
      # Member Variables
      ####################################################

      _Self._m_directory = _Directory
      _Self._m_config_file = _ConfigFile
      _Self._m_disk_file = _DiskFile
      _Self._m_disk_created = _ConfigCreated
      _Self._m_config_created = _DiskCreated

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

################################################################################
################################################################################
#
# End of class vm
#
################################################################################
################################################################################

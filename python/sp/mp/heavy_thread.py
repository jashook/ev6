################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: heavy_thread.py
#
# Modifications:
#
# 1-April-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

from multiprocessing import Process

################################################################################
################################################################################

class heavy_thread:

   def __init__(_Self, _EntryPoint, _StartArgs):
   
      #####################################################
      # Member Variables
      #####################################################

      _Self._m_exit_code = 0
      _Self._m_is_active = False
      _Self._m_is_alive = False

      _Self._m_process = Process(target = _EntryPoint, args = _StartArgs)

   def is_active(_Self):

      return _Self._m_is_active

   def is_alive(_Self):

      return _Self._m_is_alive

   def join(_Self):

      _Self._m_process.join()

   def set_active(_Self):

      _Self._m_is_active = True

   def set_alive(_Self):

      _Self._m_is_alive = True

   def sleep(_Self, _Time):

      time.sleep(_Time)

   def start(_Self):

      _Self._m_process.start()

################################################################################
################################################################################
#
# End of class heavy_thread
#
################################################################################
################################################################################
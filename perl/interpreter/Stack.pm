#!/usr/bin/perl

################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: Stack.pl
#
# Modifications:
#
# 28-Jan-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

use strict;
use warnings;

################################################################################
################################################################################

package Stack;

################################################################################
################################################################################
# Constructor
################################################################################
################################################################################

sub new {
   
   my $_Self = {

      m_array => []

   };

   bless $_Self, 'Stack';
   return $_Self;

}

################################################################################
################################################################################
# Methods
################################################################################
################################################################################

sub pop {

   my ($_Self) = @_;

   return pop(@{$_Self->{ m_array }});   

}

sub print {

   my ($_Self) = @_;

   print @{$_Self->{ m_array }};

}

sub push {
   
   my ($_Self, $_Data) = @_; 

   return push(@{$_Self->{ m_array }}, $_Data);

}

sub size {

   my ($_Self) = @_;

   return scalar(@{$_Self->{ m_array }});

}

################################################################################
################################################################################
# end of class
################################################################################
################################################################################

1

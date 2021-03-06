#!/usr/bin/perl

################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: cat.pl
#
# Modifications:
#
# 28-Jan-13: Version 1.0: Created
#
# Timeperiod ev6
#
################################################################################
################################################################################

use strict;
use warnings;

use autodie;

################################################################################
################################################################################

open (my $file, "<", "$ARGV[0]");

my @lines = <$file>;

foreach my $temp (@lines)
{
   print "$temp";
}

################################################################################
################################################################################

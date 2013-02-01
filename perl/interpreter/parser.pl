#!/usr/bin/perl

################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: parser.pl
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

use File::Basename;
use lib dirname(".");
use Line;
use Queue;
use Stack;

#################################################################################
################################################################################

sub brace_error
{

}

sub parentheses_error
{

}

###############################################################################
################################################################################

open (my $_File, "<", "$ARGV[0]") if defined $ARGV[0];

my @_Lines = <$_File> if defined $_File;

my $_Queue = new Queue;

my $_Count = 1; # start on line 1

foreach my $_Temp (@_Lines)
{
   my $_CommentIndex = index($_Temp, '#');

   if ($_CommentIndex != -1) 
   {
      print $_CommentIndex . "\n";

      print length($_Temp) . "\n";
      
      $_Temp = substr(0, $_CommentIndex);
   }

   $_Temp =~ s/^\s*(\S*(?:\s+\S+)*)\s*$/$1/;

   my @_Words = split(/\s+/, $_Temp);

   foreach my $_Word (@_Words) 
   {
      my $_Line = new Line;

      $_Line->line($_Word);
      $_Line->line_number($_Count);

      $_Queue->push($_Line);
   }

   ++$_Count;
}

for (my $i = 0, my $_Size = $_Queue->size(); $i < $_Size; ++$i)
{
   my $_Word = $_Queue->pop();

   #print $_Word->line() . " " . $_Word->line_number() . "\n";
}

#print $_Queue->{ m_array } . "\n";

#for ( my $i = 0, my $_Size = $_Queue->size(); $i < $_Size; ++$i)
#{
   #print $_Queue->push()->{ m_line_number };
#}

my $_ParenthesesStack = new Stack;
my $_BraceStack = new Stack;

=pod

for (my $i = 0, my $_Size = $_Queue->size(); $i < $_Size; ++$i)
{
   my $_Word = $_Queue->pop();

   if (index($_Word->{ m_line }, '(') != -1)
   {
      $_ParenthesesStack->push($_Word);
   }

   elsif (index($_Word->{ m_line }, ')') != -1)
   {
      my $_Line = $_ParenthesesStack.pop()->{ m_line_number };
      
      if ($_Line != $_Word->{ m_line_number }) 
      {
      
         &parentheses_error($_Line, $_Word->{ m_line_number });

      }

   }
   
   elsif (index($_Word->{ m_line }, '{') != -1)
   {
      $_BraceStack->push($_Word);
   }

   elsif (index($_Word->{ m_line }, '}') != -1)
   {
      my $_Line = $_BraceStack.pop()->{ m_line_number };

      if ($_Line != $_Word->{ m_line_number }) 
      {

         &brace_error($_Line, $_Word->{ m_line_number });

      }

   }
   
}

=cut

################################################################################
################################################################################

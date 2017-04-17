#!/usr/bin/perl -w

use strict;
use JACProtectionTool;
use IO::Handle;
use File::Temp;
use File::Basename;

my $myTool = new JACProtectionTool("./irdeto_java_access_config.xml", "build");
$myTool->init();
$myTool->execute();

